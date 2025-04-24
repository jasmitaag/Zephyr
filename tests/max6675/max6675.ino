#include "max6675.h"

int ktcSO = 8;
int ktcCS = 9;
int ktcCLK = 10;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

  
void setup() {
  Serial.begin(9600);
  delay(500);
}

void loop() {
  
   Serial.print("Deg C = "); 
   Serial.print(ktc.readCelsius());
   Serial.print("\t Deg F = ");
   Serial.println(ktc.readFahrenheit());
 
   delay(500);
}