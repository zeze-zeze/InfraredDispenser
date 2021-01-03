void setup() {
  Serial.begin(9600); 
  pinMode(7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  delay(300);
  Serial.println("test");
  digitalWrite(7, HIGH);
}
