#include <Wire.h>
#include <time.h> 
#include <LCD_I2C.h>
#include "BluetoothSerial.h"

LCD_I2C lcd(0x27, 16, 2);
BluetoothSerial SerialBT; 

#define STD_TIME FRAME/IDEAL_BOX // Time for 1 box in seconds
#define IDEAL_BOX 9 // Ideal number of boxes in 1 FRAME
#define FRAME 10 // Time Frame for 1 efficiency data

int color = 1; // 1-Black, 0-White
int count = 0; // Unit Count variable
int x_count = 0; // Temp variable to store last frame's total units
int eff = 100; // Efficiency in %age

int scl = 22; // LCD SCL pin
int sda = 21; // LCD SDA pin
int ir = 2; // IR Sensor pin

int arr_eff[] = {100, 100, 100}; // Array to store last 3 efficiencies 
long int y_time = 0;

int incoming; // incoming signal from app to esp
int BT_eff=100;
int BT_count=0;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("E-Conveyer");
  pinMode(ir, INPUT); // initialising infrared pin
  lcd.begin();
  lcd.backlight();
  lcd.noBlink();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("E-Conveyer");
  lcd.setCursor(1,1);
  lcd.print("JUGAAD - UIET");
  lcd.setCursor(0,0);
  for (int i=0; i<3; i++) {
    delay(500);
    lcd.print(" ");
  }
  lcd.setCursor(13,0);
  for (int i=0; i<3; i++) {
    delay(500);
    lcd.print(" ");
  }
  lcd.setCursor(0,1);
  for (int i=0; i<1; i++) {
    delay(500);
    lcd.print(" ");
  }
  lcd.setCursor(14,1);
  for (int i=0; i<2; i++) {
    delay(500);
    lcd.print(" ");
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Max Efficiency");
  lcd.setCursor(0,1);
  lcd.print(IDEAL_BOX);
  lcd.print(" box - ");
  lcd.print(FRAME);
  lcd.print(" sec");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Unit Count: "); // 12 chars
  lcd.setCursor(0,1);
  lcd.print("Efficiency: "); // 12 chars
}

void loop() {
  long int x_time = millis();
  
  // IR Input Data
  int ir_inp = digitalRead(ir);
  if (ir_inp != color)
  {
    color = ir_inp;
    if (color == 0)
    {
      count++;
      //SerialBT.println(1000+count);
      //Serial.println(1000+count);
    }
  }
  // Displaying Unit Count
  lcd.setCursor(12, 0);
  lcd.print(count);

  // Calculating Efficiency
  if (x_time - y_time > FRAME*1000)
  {
    eff = (count - x_count)*100/IDEAL_BOX;
    SerialBT.write(eff);
    x_count = count;
    y_time = x_time;
    
    arr_eff[0] = eff;
    arr_eff[1] = arr_eff[0];
    arr_eff[2] = arr_eff[1];
  }
  // Displaying Efficiency
  lcd.setCursor(12, 1);
  lcd.print(eff);
  lcd.print("%   s");
}
