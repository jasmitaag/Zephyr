#include <max6675.h>

// MAX6675 pin assignments
const int thermoSO = 4;  // SO = Data Out
const int thermoCS = 5;  // CS = Chip Select
const int thermoSCK = 6; // SCK = Serial Clock

// Relay control pin
const int relayPin = 8;

// Temperature thresholds
const float tempLow = 95.0;   // Turn heater ON below this
const float tempHigh = 105.0; // Turn heater OFF above this

MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Assume HIGH = relay OFF (depends on module)
  delay(500); // Allow sensor to stabilize
}

void loop() {
  float temperature = thermocouple.readCelsius();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Relay logic with hysteresis
  static bool heaterOn = false;

  if (temperature < tempLow && !heaterOn) {
    digitalWrite(relayPin, HIGH);  // Turn ON (active-low)
    heaterOn = true;
    Serial.println("Heater ON");
  } else if (temperature > tempHigh && heaterOn) {
    digitalWrite(relayPin, LOW); // Turn OFF
    heaterOn = false;
    Serial.println("Heater OFF");
  }

  delay(1000); // Wait a second
}
