# SightGuide AI

An assistive smart-navigation cap concept combining a Flutter companion app, Raspberry Pi vision/voice processing, and ESP32 sensor alerts.

> **Safety:** This repository is an early prototype scaffold, not a certified mobility aid. Never rely on it as the only means of navigation. Test with a sighted companion in a controlled environment before any real-world use.

## Repository layout

- `app/` — Flutter companion app dashboard and feature screens.
- `device/esp32/` — ESP32 ultrasonic/vibration/buzzer firmware starter.
- `ai/pi/` — Raspberry Pi Python service scaffold for camera, YOLO, OCR and voice pipelines.
- `docs/` — architecture, setup and integration notes.

## Hardware concept

- Raspberry Pi 5 + camera module for vision and speech processing.
- ESP32 + three ultrasonic sensors for near-field obstacle sensing.
- Left/right vibration motors and buzzer for alerts.
- Android phone for GPS, SOS contacts and settings.

## Quick start

### Flutter app

Install Flutter stable and Android SDK, then:

```bash
cd app
flutter pub get
flutter run
```

The initial app is a navigable UI scaffold. Hardware, cloud, GPS and AI actions are clearly marked as integration points until their services and permissions are configured.

### ESP32 firmware

Open `device/esp32/sightguide_sensors.ino` in Arduino IDE. Install the ESP32 board package, set your actual GPIO pins, and verify motor/buzzer driver circuits before powering them. Do not drive motors directly from GPIO pins.

### Raspberry Pi service

```bash
cd ai/pi
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
python main.py
```

Camera, model weights, OCR language packs, microphone and serial-port configuration must be installed/configured for your hardware.

## Development phases

1. Build and run the Flutter dashboard.
2. Validate each ultrasonic sensor and alert output on ESP32 independently.
3. Establish serial/Bluetooth messaging between Pi and ESP32.
4. Add camera inference, OCR and speech as separate testable services.
5. Add GPS/SOS permissions and consent-based emergency contacts.
6. Run supervised accessibility and reliability tests.

See `docs/ARCHITECTURE.md` and `docs/SAFETY.md` before hardware testing.
