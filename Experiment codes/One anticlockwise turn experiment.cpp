#define Tas 49900       // 49.9 ms = 49,900 µs
#define PULSE_TIME 200  // Pulse time in µs
#define Trd 500         // Delay at the end of the cycle in ms

int mosfetPin = 3;     
const int buttonPin = 2;

const int HIN[4] = {7, 6, 5, 4};
const int LIN[4] = {11, 10, 9, 8};

int coilIndex = 3;
bool buttonPressed = false;
unsigned long lastPress = 0;
const unsigned long debounceDelay = 200;

void setup() {
  delay(2000);
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW);
  pinMode(buttonPin, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(HIN[i], OUTPUT);
    pinMode(LIN[i], OUTPUT);
    digitalWrite(HIN[i], HIGH);
    digitalWrite(LIN[i], HIGH);
  }
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !buttonPressed &&
      (millis() - lastPress > debounceDelay)) {
    buttonPressed = true;
    lastPress = millis();

    delay(Trd);
    polarize(coilIndex);
    delay(Trd);
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