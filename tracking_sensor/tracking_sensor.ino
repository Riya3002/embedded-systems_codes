const int sensorPin = 8;
// const int ledPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  // pinMode(ledPin, OUTPUT);
}

void loop() {
  int val = digitalRead(sensorPin);

  if (val == LOW) {
    Serial.println("white object detected");
  }
  else {
    Serial.println("black object detected");
  }
  delay(500);
}
