#include <Servo.h>
int lightpen=A0;
int lightval;
int servopen=9;
int angle;
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  pinMode(lightpen,INPUT);
  Serial.begin(9600);
  myservo.attach(servopen);

}

void loop() {
  // put your main code here, to run repeatedly:
  lightval=analogRead(lightpen);
  Serial.println(lightval);
  delay(500);
  angle=(-16./63.)*lightval+16.*780./63.;
  myservo.write(angle);
  

}
