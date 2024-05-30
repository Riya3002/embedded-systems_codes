const int buzzer = 9;
void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  tone(buzzer, 10000);
  //digitalWrite(buzzer, HIGH);
  delay(10000);
  noTone(buzzer);
  //digitalWrite(buzzer, LOW);
  delay(10000);
}
