#include<ESP32Servo.h>
Servo myservo;
// Servo myservo1;
// Servo myservo2;

#define MotorPin1 18
void setup() {
  myservo.attach(MotorPin1); // put your setup code here, to run once:

}

void loop() {

  myservo.write(10);
  delay(100);
  myservo.write(180);
  delay(100);// put your main code here, to run repeatedly:

}
