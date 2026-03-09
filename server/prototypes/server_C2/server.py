"""
C2 (Command and Control) Server - PoC / Educational purposes only.

This server is intended for lab/study use with the silent_door backdoor.
Critical or production-ready features are intentionally omitted.
"""

import re
from datetime import datetime, timezone

from flask import Flask, request, jsonify

app = Flask(__name__)

# In-memory store for connected agents (not persistent)
agents = {}


@app.route("/", methods=["GET"])
def index():
    return jsonify({"status": "ok", "message": "C2 server running (PoC/Educational only)"}), 200


_AGENT_ID_RE = re.compile(r"^[A-Za-z0-9_\-]{1,64}$")


@app.route("/register", methods=["POST"])
def register():
    """Endpoint for a backdoor agent to register its presence."""
    if not request.is_json:
        return jsonify({"error": "content-type must be application/json"}), 415

    data = request.get_json(silent=True)
    if data is None:
        return jsonify({"error": "invalid JSON body"}), 400

    agent_id = data.get("id", "")
    if not agent_id or not _AGENT_ID_RE.match(agent_id):
        return jsonify({"error": "missing or invalid agent id (alphanumeric, 1-64 chars)"}), 400

    agents[agent_id] = {
        "id": agent_id,
        "host": str(data.get("host", "unknown"))[:128],
        "os": str(data.get("os", "unknown"))[:64],
        "last_seen": datetime.now(timezone.utc).isoformat(),
    }
    return jsonify({"status": "registered", "agent_id": agent_id}), 200


@app.route("/agents", methods=["GET"])
def list_agents():
    """Return the list of registered agents."""
    return jsonify({"agents": list(agents.values())}), 200

@app.route("/agents/<agent_id>", methods=["GET"])
def get_agent(agent_id):
    """Return details for a specific agent."""
    agent = agents.get(agent_id)
    if not agent:
        return jsonify({"error": "agent not found"}), 404
    return jsonify({"agent": agent}), 200   

if __name__ == "__main__":
    # Debug mode disabled; bind only to localhost for safety in a lab environment
    app.run(host="127.0.0.1", port=5000, debug=False)
