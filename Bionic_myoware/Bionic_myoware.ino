#include<ESP32Servo.h>
#include <Wire.h>
#include <SPI.h>

Servo myservo;
Servo myservo1;
Servo myservo2;

#define Sensorpin A0
#define MotorPin1 18
#define MotorPin2 19
#define MotorPin3 5
#define Status 0
int VALUE = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(Sensorpin,INPUT);
  myservo.attach(MotorPin1);   // Thumb [100 - 160]
  myservo1.attach(MotorPin2);  // Ring / Little [180 - 10]
  myservo2.attach(MotorPin3);  // Index / Middle [0 - 110]
  
}
void loop()
{
   VALUE = analogRead(Sensorpin);
  if(VALUE>=80 && VALUE<=140)
  { 
    myservo.write(100);
    myservo1.write(10);
    myservo2.write(150);
    
  }
  else if (VALUE<=75 && VALUE>=30)
  {
    myservo.write(30);
    myservo1.write(180);
    myservo2.write(0);
  }
}