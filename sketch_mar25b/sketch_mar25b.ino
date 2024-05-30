int ledpin=12;
int buttonpin=8;
int buttonread;
int del;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin,OUTPUT);
  pinMode(buttonpin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   buttonread=digitalRead(buttonpin);
   Serial.println(buttonread);
   delay(500);
   if(buttonread==1){
       digitalWrite(ledpin,HIGH);
       }

    else{
      digitalWrite(ledpin,LOW);
    }   

}
