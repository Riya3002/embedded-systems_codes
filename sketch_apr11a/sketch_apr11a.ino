#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define  SCREEN_ADDRESS 0x3C
#define OLED_RESET  -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int VALUE[5]={1,2,3,4,5};

void setup() {
  Serial.begin(9600);
  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
   display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("BIONIC PROSTHETIC ARM");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("FIST OPEN");
  display.display();
  delay(1000);
  display.clearDisplay();

   for(int r=0;r<5;r++){
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,28);
    display.println(VALUE[r]);
    display.display();
    delay(500);
    display.clearDisplay();}

  delay(2000);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  

  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("FIST CLOSED");
  display.display();
  delay(1000);
  display.clearDisplay();

   for(int r=0;r<5;r++){
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,28);
    display.println(VALUE[r]);
    display.display();
    delay(500);
    display.clearDisplay();}

    delay(2000);   
   }
   void loop(){}