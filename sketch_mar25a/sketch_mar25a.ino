// passive buzzer program
int lightpin=A0;
int buzzpin=8;
int delayt;
int lightval;
void setup() {  
  pinMode(lightpin,INPUT);
  pinMode(buzzpin,OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  lightval=analogRead(lightpin);
  delayt=(9./550.)*lightval -(9.*200./550.) + 1. ;
  digitalWrite(buzzpin, HIGH);
  delay(delayt);
  digitalWrite(buzzpin, LOW);
  delay(delayt);
}