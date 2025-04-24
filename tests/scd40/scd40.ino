#include <Wire.h>
#include "SensirionI2cScd4x.h"

SensirionI2cScd4x scd4x;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for Serial

  Wire.begin();  // For ESP32: default SDA = GPIO21, SCL = GPIO22

  uint16_t error;

  // Begin sensor with Wire and address (0x62 is default)
  scd4x.begin(Wire, 0x62);

  // Stop any prior measurement
  error = scd4x.stopPeriodicMeasurement();
  if (error) {
    Serial.print("Stop measurement failed! Error code: ");
    Serial.println(error);
  }

  // Start periodic measurement
  error = scd4x.startPeriodicMeasurement();
  if (error) {
    Serial.print("Start measurement failed! Error code: ");
    Serial.println(error);
  }

  Serial.println("Waiting for first measurement...");
  delay(5000);  // First reading takes ~5 seconds
}

void loop() {
  uint16_t error;
  bool dataReady = false;

  error = scd4x.getDataReadyStatus(dataReady);
  if (error) {
    Serial.print("DataReadyStatus failed! Error code: ");
    Serial.println(error);
    return;
  }

  if (!dataReady) {
    delay(1000);
    return;
  }

  uint16_t co2;
  float temperature, humidity;

  error = scd4x.readMeasurement(co2, temperature, humidity);
  if (error) {
    Serial.print("ReadMeasurement failed! Error code: ");
    Serial.println(error);
  } else {
    Serial.print("CO₂: ");
    Serial.print(co2);
    Serial.print(" ppm, Temp: ");
    Serial.print(temperature);
    Serial.print(" °C, RH: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  delay(5000);
}