int Inputpin = A0;
int Inputpin1 = A1;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  pinMode(Inputpin, INPUT);
  pinMode(Inputpin1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int out = analogRead(Inputpin);
 Serial.print("EMG1:");
 Serial.print(out);
 delay(500);
 int out1 = analogRead(Inputpin1);
 Serial.print("EMG2:");
 Serial.println(out1);
 delay(500);
}
