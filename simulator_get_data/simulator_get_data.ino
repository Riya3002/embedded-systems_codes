#include<ESP32Servo.h>
#include <Wire.h>
#include <SPI.h>

Servo myservo;
Servo myservo1;
Servo myservo2;

#define MotorPin1 18
#define MotorPin2 19
#define MotorPin3 21
#define Status 0
int VALUE = 0;
int TA[7] = { 13, 12, 14,27,26,25,33};
int triggerPin = 32;
int sensorValue = 0;

int getData() {
  int binary[7];
  int dec = 0, m = 1, d = 64;
  for (int i = 0; i < 7; i++) {
    binary[i] = digitalRead(TA[i]);
  }
  for (int i = 0; i < 7; i++) {
    m = 1;
    for (int j = 6; j > i; j--) {
      m = m * 2;
    }
    dec = dec + binary[i] * m;
  }
  return dec;
}

void setup()
{
  Serial.begin(9600);
 
  myservo.attach(MotorPin1);   // Thumb [100 - 160]
  myservo1.attach(MotorPin2);  // Ring / Little [180 - 10]
  myservo2.attach(MotorPin3);  // Index / Middle [0 - 110]
    for (int i = 0; i < 7; i++) {
    pinMode(TA[i], INPUT);
  }
  pinMode(triggerPin, INPUT);
  
}
void loop()
{
   VALUE = getData();
  // if(VALUE>=80 && VALUE<=140)
  // { 
  //   myservo.write(100);
  //   myservo1.write(10);
  //   myservo2.write(150);
    
  // }
  // else if (VALUE<=75 && VALUE>=30)
  // {
  //   myservo.write(30);
  //   myservo1.write(180);
  //   myservo2.write(0);
  // }
  Serial.println(VALUE);
}