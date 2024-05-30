 int mypin=A3;
  int output=6;
  int potval;
  int ledval;



void setup() {
  // put your setup code here, to run once:
  pinMode(mypin,INPUT);
  pinMode(output, OUTPUT);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  potval=analogRead(mypin);
  ledval=(255./1023.)*potval;
  analogWrite(output,ledval);
  Serial.println(ledval);
  delay(100);
  }
