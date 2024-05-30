// int p1=9;
// int p2=4;
// int p3=5;
// int p4=6;
// int mypin=A3;
// int readval;
// float v2;

// void setup() {
//   // put your setup code here, to run once:
// // pinMode(read, OUTPUT);
// // pinMode(p2, OUTPUT);
// // pinMode(p3, OUTPUT);
// // pinMode(p4, OUTPUT);
// Serial.begin(9600);
// }

// void loop() {
// readval=analogRead(mypin);
// v2=(5./1023.)*readval;
// Serial.println(v2);
// delay(600);

 // put your main code here, to run repeatedly:
// digitalWrite(p1,LOW);
// digitalWrite(p2,LOW);
// digitalWrite(p3,LOW);
// digitalWrite(p4,LOW);
// delay(1000);
// digitalWrite(p1,HIGH);
// digitalWrite(p2,LOW);
// digitalWrite(p3,LOW);
// digitalWrite(p4,LOW);
// delay(1000);
// digitalWrite(p1,LOW);
// digitalWrite(p2,HIGH);
// digitalWrite(p3,LOW);
// digitalWrite(p4,LOW);
// delay(1000);
// digitalWrite(p1,HIGH);
// digitalWrite(p2,HIGH);
// digitalWrite(p3,LOW);
// digitalWrite(p4,LOW);
// delay(1000);
// digitalWrite(p1,LOW);
// digitalWrite(p2,LOW);
// digitalWrite(p3,HIGH);
// digitalWrite(p4,LOW);
// delay(1000);
// digitalWrite(p1,HIGH);
// digitalWrite(p2,LOW);
// digitalWrite(p3,HIGH);
// digitalWrite(p4,LOW);
// delay(1000);
// digitalWrite(p1,LOW);
// digitalWrite(p2,HIGH);
// digitalWrite(p3,HIGH);
// digitalWrite(p4,LOW);
// delay(1000);
// digitalWrite(p1,HIGH);
// digitalWrite(p2,HIGH);
// digitalWrite(p3,HIGH);
// digitalWrite(p4,LOW);
// delay(1000);
// digitalWrite(p1,LOW);
// digitalWrite(p2,LOW);
// digitalWrite(p3,LOW);
// digitalWrite(p4,HIGH);
// delay(1000);
// digitalWrite(p1,HIGH);
// digitalWrite(p2,LOW);
// digitalWrite(p3,LOW);
// digitalWrite(p4,HIGH);
// delay(1000);
// digitalWrite(p1,LOW);
// digitalWrite(p2,HIGH);
// digitalWrite(p3,LOW);
// digitalWrite(p4,HIGH);
// delay(1000);
// digitalWrite(p1,HIGH);
// digitalWrite(p2,HIGH);
// digitalWrite(p3,LOW);
// digitalWrite(p4,HIGH);
// delay(1000);

// digitalWrite(13,HIGH);
// delay(3000);
// analogWrite(p1,20);
// delay(500);
// analogWrite(p1,30);
// delay(500);
// analogWrite(p1,80);
// delay(500);
// analogWrite(p1,150);
// delay(500);
// analogWrite(p1,200);
// delay(500);
// analogWrite(p1,255);
// delay(500);
  // }


// int j;


// void setup() {
//   // put your setup code here, to run once:
// Serial.begin(9600);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   // for (j=1;j<=10;j=j+1){
//   //   Serial.println(j);
//   //   delay(500);
//   // }
//   // Serial.println();
// }

// int myNumber;
// String msg="what is your number";
// String msg2="your number : ";

//  void setup(){
//   Serial.begin(9600);

// }

//  void loop(){
//   Serial.println(msg);
//   while (Serial.available()==0){
   

//   }
//   myNumber=Serial.parseInt();
//   Serial.print(msg2);
//   Serial.println(myNumber); 
// }










// int redPin=8;
// int greenPin=9;
// int bluePin=10;
// String myColor;

// void setup() {
  
//   Serial.begin(9600);
//   pinMode (redPin,OUTPUT);
//   pinMode (greenPin,OUTPUT);
//   pinMode (bluePin,OUTPUT);
// }





// int mybuzz;
// int buzzpin=8;
// String msg ="enter your number";
// void setup() {
// Serial.begin(9600);
// pinMode(buzzpin,OUTPUT);
// }

// void loop(){
//   Serial.println(msg);
//   While (Serial.available()==0){
    
//   }
// }









// int mybuzz=8;
// int d1=500;
// int d2=50;
// int j;

// void setup(){
//   // Serial.begin(9600);
//   pinMode(mybuzz,OUTPUT);

// }
// void loop(){
//   for (j=0;j<20;j=j+1){
//     digitalWrite(mybuzz,HIGH);
//     delay(d1);
//     digitalWrite(mybuzz,LOW);    
//     delay(d1);

//   }
//   for (j=0;j<20;j=j+1){
//     digitalWrite(mybuzz,HIGH);
//     delay(d2);
//     digitalWrite(mybuzz,LOW);    
//     delay(d2);
    
//   }
   
// }


int buzzpin=8;
int delay1=1;
int delay2=8;
void setup(){
pinMode(buzzpin,OUTPUT);
  
}

void loop(){
digitalWrite(buzzpin,HIGH);
delay(delay1);
digitalWrite(buzzpin,LOW);
delay(delay2);
}
