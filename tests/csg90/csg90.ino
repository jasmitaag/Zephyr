#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 

void setup() {
  myservo.attach(10);
  myservo.write(115);
}

void loop() {
}