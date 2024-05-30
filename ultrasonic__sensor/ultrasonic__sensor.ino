#define TRIGER 2
#define ECHO 4

void setup() {
 pinMode(TRIGER,OUTPUT);
 pinMode(ECHO,INPUT);
 Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIGER,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGER,HIGH);
  delayMicroseconds(10);

  long x =pulseIn(ECHO,HIGH);
  long inches =   x / 74 /2;
  long cm = x /29/2;
  Serial.print(inches);
  Serial.print("in\  ");
  Serial.print(cm);
  Serial.println("cm");
 delay(500);
  if(cm<10) {
    Serial.println("stop");
  }
  else{
    Serial.println("okay");
  }
  delay(300);
}