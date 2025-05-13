#include <max6675.h>
#include <Servo.h>

// === MAX6675 Thermocouple Setup ===
const int thermoSO = 8;     // SO = Data Out
const int thermoCS = 9;     // CS = Chip Select
const int thermoSCK = 10;   // SCK = Serial Clock
MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

// === Relay Pin Setup ===
const int relayPin = 4;
const float tempLow = 95.0;    // Heater ON below this
const float tempHigh = 105.0;  // Heater OFF above this
bool heaterOn = false;

// === Servo & Button Setup ===
Servo myServo;
const int buttonPin = 2;
int lastButtonState = HIGH;
int currentButtonState;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int servoState = 0;  // 0: Stop, 1: Open, 2: Stop, 3: Close

void setup() {
  Serial.begin(9600);

  // Heater setup
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Relay OFF initially (active LOW)

  // Servo setup
  myServo.attach(11);
  myServo.writeMicroseconds(1500);  // Initial Stop
  Serial.println("System Initialized");
}

void loop() {
  // === Temperature & Heater Control ===
  float temperature = thermocouple.readCelsius();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature < tempLow && !heaterOn) {
    digitalWrite(relayPin, HIGH);  // Heater ON (active-low)
    heaterOn = true;
    Serial.println("Heater ON");
  } else if (temperature > tempHigh && heaterOn) {
    digitalWrite(relayPin, LOW);   // Heater OFF
    heaterOn = false;
    Serial.println("Heater OFF");
  }

  // === Button Debounce and Servo Control ===
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && currentButtonState == HIGH) {
      servoState = (servoState + 1) % 4; // Cycle: 0 → 1 → 2 → 3 → 0
      switch (servoState) {
        case 0:
          myServo.writeMicroseconds(1500);  // Stop
          Serial.println("State 0: Servo Stop");
          break;
        case 1:
          myServo.writeMicroseconds(1725);  // Slow CW
          Serial.println("State 1: Servo Opening");
          break;
        case 2:
          myServo.writeMicroseconds(1500);  // Stop
          Serial.println("State 2: Servo Stop");
          break;
        case 3:
          myServo.writeMicroseconds(1300);  // Slow CCW
          Serial.println("State 3: Servo Closing");
          break;
      }
    }
    currentButtonState = reading;
  }

  lastButtonState = reading;
  delay(500);

  
}
