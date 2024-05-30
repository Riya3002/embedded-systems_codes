#include<Servo.h>
Servo myservo;
Servo myservo1;
Servo myservo2;

#define Sensorpin 18
#define MotorPin1 5
#define MotorPin2 17
#define MotorPin3 16
#define Status 0

// #define OLED_WIDTH 128
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define  SCREEN_ADDRESS 0x3C
// #define OLED_RESET  -1
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
{
  Serial.begin(9600);
  
  // initialize the OLED object
  // if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for(;;); // Don't proceed, loop forever
  // }
  // display.clearDisplay();

  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(2,32);
  // display.println("BIONIC PROSTHETIC ARM");
  // display.display();
  // delay(2000);
  // display.clearDisplay();
  pinMode(Sensorpin,INPUT);
  myservo.attach(MotorPin1);   // Thumb [100 - 160]
  myservo1.attach(MotorPin2);  // Ring / Little [180 - 10]
  myservo2.attach(MotorPin3);  // Index / Middle [0 - 110]
  
}

void loop()
{
  
   int VALUE = digitalRead(Sensorpin);
   Serial.println(VALUE);
  if(VALUE==0)
  { 
    myservo.write(100);
    myservo1.write(10);
    myservo2.write(150);
    //  display.clearDisplay();

  // display.setTextSize(1.5);
  // display.setTextColor(WHITE);
  // display.setCursor(15,32);
  // display.println("FIST OPEN");
  // display.display();
  // delay(200);
  // display.clearDisplay();
  // }
  else if (VALUE==1)
  {
    myservo.write(30);
    myservo1.write(180);
    myservo2.write(0);
    //  display.clearDisplay();

  // display.setTextSize(1.5);
  // display.setTextColor(WHITE);
  // display.setCursor(15,32);
  // display.println("FIST CLOSED");
  // display.display();
  // delay(200);
  // display.clearDisplay();
  // }
  // delay(50);
}
