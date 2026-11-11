# SightGuide AI architecture

## Data flow

1. Camera + microphone feed the Raspberry Pi 5.
2. The Pi hosts vision and speech pipelines: object detection, OCR and optional consent-based familiar-person recognition.
3. ESP32 samples front/left/right ultrasonic sensors and drives left/right vibration outputs and buzzer through protected driver circuits.
4. ESP32 sends timestamped sensor readings to the Pi over USB serial (Bluetooth can be added later).
5. Flutter companion app presents device state, navigation, configuration and SOS workflows.

## Proposed message contract

ESP32 serial JSON line:

```json
{"front_cm":82.4,"left_cm":145.0,"right_cm":64.2}
```

Pi endpoints in the starter service:

- `GET /health` — service health.
- `GET /sensors` — latest sensor snapshot.

## Integration sequence

- Confirm board GPIO and voltage levels; many ESP32 boards use 3.3 V logic. Use a divider/level shifter where a sensor echo output is 5 V.
- Validate each sensor's range, blind spots and cross-talk; stagger measurements.
- Add a stable transport protocol and reconnect logic.
- Add camera inference with a lightweight model and measured latency on the Pi.
- Add OCR and text-to-speech as independent pipelines.
- Add app permissions and secure pairing; never expose an unauthenticated device API to the public internet.
- Add GPS and SOS only after contact verification, consent and failure handling.

## Important limitations

Ultrasonic sensors cannot reliably detect every surface, drop-off, overhead obstacle, transparent object or fast-moving hazard. Camera distance estimates require calibration and can fail in poor lighting. This prototype must not be represented as a certified mobility aid.
