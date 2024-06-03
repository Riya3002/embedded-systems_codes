#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,8,9,10,11);
int tacswitch = 6;
int tacpin = 7;
int x;
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  pinMode(tacswitch,INPUT);
  pinMode(tacpin,INPUT);
}

void loop()
{
   lcd.setCursor(0,0);
   lcd.print("value=");
  
  int tacvalue=0;
  int tacvalue2=0;
  tacvalue = analogRead(tacswitch);
  tacvalue2 = analogRead(tacpin);


  if(tacvalue==1){
   x=1;
  
  }
 
      	lcd.setCursor(1,1);
  	lcd.print(" ");
  	lcd.setCursor(0,1);
  	lcd.println(1);
    delay(100);
  if(tacvalue2==1){
  x=2;
  }
 
 	lcd.setCursor(1,1);
  	lcd.print(" "); 
  	lcd.setCursor(0,1);
   	lcd.println(x);
    delay(100);
  
  
  
 }