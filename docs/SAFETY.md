# Safety, privacy and responsible testing

- This prototype is not a certified assistive or medical device and must not be the user's sole navigation aid.
- Keep using established mobility aids and travel practices. Test only in controlled, supervised environments.
- Never test obstacle alerts near roads, stairs, traffic, platforms or other dangerous environments.
- Validate sensor coverage, latency, battery behavior and failure modes before any supervised pilot.
- Drive vibration motors and buzzers using correctly rated transistor/MOSFET circuits and a suitable power supply; do not connect motors directly to ESP32 pins.
- Verify sensor echo voltage compatibility with ESP32 3.3 V GPIO.
- Familiar-person recognition must be opt-in, limited to enrolled consenting people, and provide deletion controls. Prefer on-device processing and avoid retaining raw camera frames.
- Store SOS contacts only with user consent. Show the recipient and location before sending during setup; provide a clear cancel path and handle unavailable GPS/network.
- Request only necessary Android permissions and explain why each is needed.
