#include <Arduino.h>
#include <Wire.h>
#include <SensirionI2cScd4x.h>
#include <max6675.h>

// CO2 Sensor Definitions
SensirionI2cScd4x scd4x;
static char errorMessage[64];
static int16_t error;

// MAX6675 Thermocouple Definitions
const int thermoSO = 8;    // SO = Data Out
const int thermoCS = 9;    // CS = Chip Select
const int thermoSCK = 10;  // SCK = Serial Clock
MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

// Relay Control
const int relayPin = 4;
const float tempLow = 36;   // Turn heater ON below this
const float tempHigh = 41; // Turn heater OFF above this
static bool heaterOn = false;

// CO2 Sensor Macros
#ifdef NO_ERROR
#undef NO_ERROR
#endif
#define NO_ERROR 0

void PrintUint64(uint64_t& value) {
    Serial.print("0x");
    Serial.print((uint32_t)(value >> 32), HEX);
    Serial.print((uint32_t)(value & 0xFFFFFFFF), HEX);
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(100);
    }

    // Initialize I2C and CO2 Sensor
    Wire.begin();
    scd4x.begin(Wire, SCD41_I2C_ADDR_62);

    uint64_t serialNumber = 0;
    delay(30);
    error = scd4x.wakeUp();
    scd4x.stopPeriodicMeasurement();
    scd4x.reinit();

    error = scd4x.getSerialNumber(serialNumber);
    if (error != NO_ERROR) {
        Serial.print("Error getting serial number: ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
    } else {
        Serial.print("SCD4x serial number: ");
        PrintUint64(serialNumber);
        Serial.println();
    }

    error = scd4x.startPeriodicMeasurement();
    if (error != NO_ERROR) {
        Serial.print("Error starting periodic measurement: ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
    }

    // Initialize Relay Control
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW); // Assume LOW = heater OFF
    delay(500); // Thermocouple stabilization
}

void loop() {
    // Wait 5 seconds
    delay(5000);

    // --- CO2 Sensor Readings ---
    bool dataReady = false;
    error = scd4x.getDataReadyStatus(dataReady);
    if (error != NO_ERROR) {
        Serial.println("Error checking data ready");
        return;
    }

    while (!dataReady) {
        delay(100);
        error = scd4x.getDataReadyStatus(dataReady);
        if (error != NO_ERROR) {
            Serial.println("Error polling data ready");
            return;
        }
    }

    uint16_t co2 = 0;
    float temp = 0.0;
    float rh = 0.0;
    error = scd4x.readMeasurement(co2, temp, rh);
    if (error == NO_ERROR) {
        Serial.print("CO2 [ppm]: ");
        Serial.print(co2);
        Serial.print(" | Temp [°C]: ");
        Serial.print(temp);
        Serial.print(" | RH [%]: ");
        Serial.println(rh);
    } else {
        Serial.println("Error reading CO2 sensor data");
    }

    // --- Thermocouple Heater Control ---
    float heaterTemp = thermocouple.readCelsius();
    Serial.print("Thermocouple Temp: ");
    Serial.print(heaterTemp);
    Serial.print(" °C | Heater: ");

    if (heaterTemp < tempLow && !heaterOn) {
        digitalWrite(relayPin, HIGH);  // Turn heater ON (active-high or -low depending on module)
        heaterOn = true;
        Serial.println("ON");
    } else if (heaterTemp > tempHigh && heaterOn) {
        digitalWrite(relayPin, LOW);  // Turn heater OFF
        heaterOn = false;
        Serial.println("OFF");
    } else {
        Serial.println(heaterOn ? "ON" : "OFF");
    }
}
