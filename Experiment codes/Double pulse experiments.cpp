#define Tas 49900       // 49.9 ms = 49,900 µs
#define PULSE_TIME 200 // Pulse time in µs PREV 200
#define Trd 500         // Delay at the end of the cycle in ms

int mosfetPin = 3;     // MOSFET control pin
const int buttonPin = 2;

const int HIN[4] = {7, 6, 5, 4};   // High-side relay pins
const int LIN[4] = {11, 10, 9, 8}; // Low-side relay pins

const int coilA = 3;   // Coil static
const int coilB = 2;   // Coil moving

bool buttonPressed = false;
unsigned long lastPress = 0;
const unsigned long debounceDelay = 200; // ms

void setup() {
  delay(2000);  // Power stabilization delay
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW);
  pinMode(buttonPin, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(HIN[i], OUTPUT);
    pinMode(LIN[i], OUTPUT);
    digitalWrite(HIN[i], HIGH); // Relay off
    digitalWrite(LIN[i], HIGH); // Relay off
  }
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !buttonPressed && (millis() - lastPress > debounceDelay)) {
    buttonPressed = true;
    lastPress = millis();

    delay(Trd);
    // reversePolarize(coilA);
    // polarize(coilA);
    // polarize(coilB);
    doublepulse1(coilB, coilA);
    delay(Trd*5);
    reversePolarize(coilA);
  }

  if (digitalRead(buttonPin) == HIGH) {
    buttonPressed = false;
  }
}

void polarize(int coil) {
  digitalWrite(HIN[coil], LOW);
  delayMicroseconds(Tas);
  digitalWrite(mosfetPin, HIGH);
  delayMicroseconds(PULSE_TIME);
  digitalWrite(mosfetPin, LOW);
  delayMicroseconds(Tas);
  digitalWrite(HIN[coil], HIGH);
}

void reversePolarize(int coil) {
  digitalWrite(LIN[coil], LOW);
  delayMicroseconds(Tas);
  digitalWrite(mosfetPin, HIGH);
  delayMicroseconds(PULSE_TIME);
  digitalWrite(mosfetPin, LOW);
  delayMicroseconds(Tas);
  digitalWrite(LIN[coil], HIGH);
}

void doublepulse1(int coil1, int coil2) {
  digitalWrite(HIN[coil1], LOW);
  digitalWrite(HIN[coil2], LOW);
  delayMicroseconds(Tas);
  digitalWrite(mosfetPin, HIGH);
  delayMicroseconds(PULSE_TIME);
  digitalWrite(mosfetPin, LOW);
  delayMicroseconds(Tas);
  digitalWrite(HIN[coil1], HIGH);
  digitalWrite(HIN[coil2], HIGH);
  }