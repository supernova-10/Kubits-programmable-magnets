

#define Tas 49900                  // 49.9 ms = 49,900 µs // Time to wait for relay contacts to settle (ms) PREV25
#define PULSE_TIME 200                  // Time to energize the coil in either direction (ms)
#define Trd 500                        // Time to wait at the end of the cycle (ms)

int mosfetPin = 3;     // MOSFET control pin
// const int buttonPin = 2;

// Relay control pins for 4 coils (active-low relays)
const int HIN[4] = {7, 6, 5, 4};
const int LIN[4] = {11, 10, 9, 8};

void setup() {
  delay(2000);
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW);
  // pinMode(buttonPin, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(HIN[i], OUTPUT);
    pinMode(LIN[i], OUTPUT);
    digitalWrite(HIN[i], HIGH); // relay off
    digitalWrite(LIN[i], HIGH); // relay off
  }

}

void loop() {
  for (int i=0; i<4; i++){
    delay(Trd);
    reversePolarize(i);
    delay(Trd);
    polarize(i);  }
}


void polarize(int coil) {
  digitalWrite(HIN[coil], LOW);   // HIN ON
  delayMicroseconds(Tas);
  digitalWrite(mosfetPin, HIGH);
  delayMicroseconds(PULSE_TIME);
  digitalWrite(mosfetPin, LOW);
  delayMicroseconds(Tas);
  digitalWrite(HIN[coil], HIGH);   // HIN OFF
}

void reversePolarize(int coil) {
  digitalWrite(LIN[coil], LOW);   // LIN ON
  delayMicroseconds(Tas);
  digitalWrite(mosfetPin, HIGH);
  delayMicroseconds(PULSE_TIME);
  digitalWrite(mosfetPin, LOW);
  delayMicroseconds(Tas);
  digitalWrite(LIN[coil], HIGH);   // LIN OFF
}