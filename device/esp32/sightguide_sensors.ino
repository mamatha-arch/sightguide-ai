// SightGuide AI — ESP32 ultrasonic alert starter
// IMPORTANT: choose GPIOs for your exact ESP32 board. Use transistor/MOSFET drivers
// for vibration motors and a suitable driver for the buzzer; never power motors from GPIO.

const int TRIG_FRONT = 5, ECHO_FRONT = 18;
const int TRIG_LEFT = 17, ECHO_LEFT = 16;
const int TRIG_RIGHT = 4, ECHO_RIGHT = 19;
const int MOTOR_LEFT = 25, MOTOR_RIGHT = 26, BUZZER = 27;
const float ALERT_CM = 120.0;

float readCm(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(3);
  digitalWrite(trig, HIGH); delayMicroseconds(10); digitalWrite(trig, LOW);
  unsigned long duration = pulseIn(echo, HIGH, 25000UL);
  if (duration == 0) return -1.0;
  return duration * 0.0343f / 2.0f;
}

void setup() {
  Serial.begin(115200);
  int outputs[] = {TRIG_FRONT, TRIG_LEFT, TRIG_RIGHT, MOTOR_LEFT, MOTOR_RIGHT, BUZZER};
  for (int pin : outputs) pinMode(pin, OUTPUT);
  pinMode(ECHO_FRONT, INPUT); pinMode(ECHO_LEFT, INPUT); pinMode(ECHO_RIGHT, INPUT);
}

void loop() {
  float front = readCm(TRIG_FRONT, ECHO_FRONT);
  delay(30); float left = readCm(TRIG_LEFT, ECHO_LEFT);
  delay(30); float right = readCm(TRIG_RIGHT, ECHO_RIGHT);
  bool f = front > 0 && front < ALERT_CM;
  bool l = left > 0 && left < ALERT_CM;
  bool r = right > 0 && right < ALERT_CM;
  digitalWrite(MOTOR_LEFT, l ? HIGH : LOW);
  digitalWrite(MOTOR_RIGHT, r ? HIGH : LOW);
  digitalWrite(BUZZER, f ? HIGH : LOW);
  Serial.printf("{\"front_cm\":%.1f,\"left_cm\":%.1f,\"right_cm\":%.1f}\n", front, left, right);
  delay(80);
}
