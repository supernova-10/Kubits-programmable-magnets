#define Tas 49900         // µs
#define PULSE_TIME 200    // µs
#define Trd 150           // ms

int mosfetPin = 3;
const int buttonPin = 2;

const int HIN[4] = {7, 6, 5, 4};   // High-side relay pins
const int LIN[4] = {11, 10, 9, 8}; // Low-side relay pins

bool buttonPressed = false;
unsigned long lastPress = 0;
const unsigned long debounceDelay = 200; // ms

int sequence[] = {1, 0, 3, 2};
int stepIndex = 0;
const int totalSteps = sizeof(sequence) / sizeof(sequence[0]);

void setup() {
  delay(2000);
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW);
  pinMode(buttonPin, INPUT);  // Use INPUT_PULLUP if needed

  for (int i = 0; i < 4; i++) {
    pinMode(HIN[i], OUTPUT);
    pinMode(LIN[i], OUTPUT);
    digitalWrite(HIN[i], HIGH);
    digitalWrite(LIN[i], HIGH);
  }
}

void loop() {
  if (digitalRead(buttonPin) == HIGH && !buttonPressed && (millis() - lastPress > debounceDelay)) {
    buttonPressed = true;
    lastPress = millis();

    int coil = sequence[stepIndex];
    reversePolarize(coil);
    delay(Trd);
    polarize(coil);
    delay(Trd);

    // Move to next coil in sequence
    stepIndex = (stepIndex + 1) % totalSteps; // Automatically loops forever
  }

  if (digitalRead(buttonPin) == LOW) {
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
