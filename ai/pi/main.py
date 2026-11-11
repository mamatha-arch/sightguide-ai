"""SightGuide AI Raspberry Pi service starter.

This intentionally exposes a health endpoint and serial telemetry reader only.
Add camera inference, OCR and speech components as isolated modules after validating
hardware. Do not treat sensor readings as guaranteed collision avoidance.
"""
import json
import os
import threading
import time
from typing import Any

from fastapi import FastAPI
import uvicorn

app = FastAPI(title="SightGuide AI Device Service", version="0.1.0")
latest: dict[str, Any] = {"connected": False, "front_cm": None, "left_cm": None, "right_cm": None, "updated_at": None}


def serial_reader() -> None:
    try:
        import serial  # pyserial
        port = os.getenv("SIGHTGUIDE_SERIAL_PORT", "/dev/ttyUSB0")
        baud = int(os.getenv("SIGHTGUIDE_BAUD", "115200"))
        with serial.Serial(port, baud, timeout=1) as device:
            latest["connected"] = True
            while True:
                raw = device.readline().decode("utf-8", errors="ignore").strip()
                if not raw:
                    continue
                try:
                    data = json.loads(raw)
                    for key in ("front_cm", "left_cm", "right_cm"):
                        if key in data:
                            latest[key] = data[key]
                    latest["updated_at"] = time.time()
                except json.JSONDecodeError:
                    continue
    except Exception as exc:
        latest["connected"] = False
        latest["error"] = str(exc)


@app.on_event("startup")
def start_reader() -> None:
    if os.getenv("SIGHTGUIDE_SERIAL_ENABLED", "false").lower() == "true":
        threading.Thread(target=serial_reader, daemon=True).start()


@app.get("/health")
def health() -> dict[str, str]:
    return {"status": "ok", "service": "sightguide-ai"}


@app.get("/sensors")
def sensors() -> dict[str, Any]:
    return latest


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=int(os.getenv("PORT", "8000")))
