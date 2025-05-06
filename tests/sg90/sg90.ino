#include <Servo.h>

Servo myServo;
int buttonPin = 2;

int lastButtonState = HIGH;
int currentButtonState;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int state = 0;  // 0: Stop, 1: Open, 2: Stop, 3: Close

void setup() {
  Serial.begin(9600);
  myServo.attach(9);  // Servo on pin 9
  pinMode(buttonPin, INPUT_PULLUP);  // Button connected to GND
  myServo.writeMicroseconds(1500);  // Initial stop
  Serial.println("Initialized. State 0: Stop");
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Debounce check
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && currentButtonState == HIGH) {
      state = (state + 1) % 4;  // Cycle: 0 → 1 → 2 → 3 → 0 ...

      switch (state) {
        case 0:
          myServo.writeMicroseconds(1500);  // Stop
          Serial.println("State 0: Stop");
          break;
        case 1:
          myServo.writeMicroseconds(1725);  // Slow CW (Open)
          Serial.println("State 1: Opening (slow CW)");
          break;
        case 2:
          myServo.writeMicroseconds(1500);  // Stop
          Serial.println("State 2: Stop");
          break;
        case 3:
          myServo.writeMicroseconds(1300);  // Slow CCW (Close)
          Serial.println("State 3: Closing (slow CCW)");
          break;
      }
    }
    currentButtonState = reading;
  }

  lastButtonState = reading;
}
