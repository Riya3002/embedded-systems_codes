// push buttons as toggle switches

int ledstate;
int btnold=1;
int btnnew;
int buttonpin=12;
int ledpin=8;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
  pinMode(buttonpin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  btnnew=digitalRead(buttonpin);
  if(btnold==0 && btnnew==1){
       if(ledstate==0){
         digitalWrite(ledpin,HIGH);
         ledstate=1;
       }
       else{
         digitalWrite(ledpin,LOW);
         ledstate=0;
       }
  }
btnold=btnnew;
delay(250);
}
x