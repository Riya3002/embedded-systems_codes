
int TA[7] = { 13,12,14,27,26,25,33 };  // Tranfer Pins Array
const int buttonPin = 13;
int buttonState = 0;
int triggerPin= 32;
void sendData(int decimal) {
  
  int binary[7];
  int q, d = 64;
  for (int i = 0; i < 7; i++) {
    binary[i] = decimal / d;
    decimal = decimal % d;
    d = d / 2;
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(TA[i], binary[i]);
  }
  digitalWrite(triggerPin, HIGH);
  // delay(100);
  digitalWrite(triggerPin, LOW);
}
void fo() {
  // thumb
  int rand1 = random(45, 60);
  Serial.print("TO :");
  Serial.println(rand1);
  sendData(rand1);

  int rand2 = random(30, 40);
  Serial.print("MIO:");
  Serial.println(rand2);
  sendData(rand2);

  int rand3 = random(40, 50);
  Serial.print("RLO:");
  Serial.println(rand3);
  sendData(rand3);
  // delay(5000);
}
void fc() {
  int rand1 = random(100, 120);
  Serial.print("TC :");
  Serial.println(rand1);
  sendData(rand1);

  int rand2 = random(70, 80);
  Serial.print("MIC:");
  Serial.println(rand2);
  sendData(rand2);
  int rand3 = random(75, 90);
  Serial.print("RLC:");
  Serial.println(rand3);
  sendData(rand3);
}
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(buttonPin, INPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(TA[i], OUTPUT);
  }
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
}
void loop() {
  buttonState = digitalRead(buttonPin);
  // if (buttonState == HIGH) {
  //   fc();
  // } else {
  //   fo();
    fc();
  
  
}
