int relay = 4; // Plug the relay into Digital Pin 13

void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
}

void loop() {
  Serial.println("Relay ON");
  digitalWrite(relay, HIGH);
  delay(1000);

  Serial.println("Relay OFF");
  digitalWrite(relay, LOW);
  delay(1000);
}
