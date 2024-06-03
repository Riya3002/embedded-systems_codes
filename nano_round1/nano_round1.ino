int ir1 = PB11; // input pin for front-left IRsensor 
int ir2 = PB10; // input pin for front-right IRsensor
int ir3 = PA5; // input pin for left IRsensor
int ir4 = PA4; // input pin for right IRsensor
float duration1, distance1_cm;
float duration2, distance2_cm;
int value1,value2,value3, value4;
int trigPin1 = PA8;    // TRIG pin for Ultrasonic1
int echoPin1 = PB8;    // ECHO pin for Ultrasonic1
int trigPin2 = PB1;    // TRIG pin for Ultrasonic2
int echoPin2 = PA0; 
int straight_time = 670;
int left_delay  = 700;
int right_delay = 700;
int uturn_delay = 1400;
//Motor_1 connection 
#define ENABLE_1 PA9
#define MOTOR1_A PB15
#define MOTOR1_B PB14
// Motor_2 Connection
#define ENABLE_2 PB6
#define MOTOR2_A PB3
#define MOTOR2_B PA15

void direction(int en1,int en2){
  analogWrite(ENABLE_1, en1);
  analogWrite(ENABLE_2, en2);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , HIGH);
  digitalWrite(MOTOR2_B , LOW);
}

void left_turn(){
  int prev_time = 0; 
  analogWrite(ENABLE_1, 150);
  analogWrite(ENABLE_2, 250);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , LOW);
  digitalWrite(MOTOR2_B , HIGH);
  int current_time = millis();
  if(current_time - prev_time == left_delay){
    digitalWrite(MOTOR1_A , LOW);
    digitalWrite(MOTOR1_B , LOW);
    digitalWrite(MOTOR2_A , LOW);
    digitalWrite(MOTOR2_B , LOW);
    delay(800);
  }
  prev_time = current_time;
}

void right_turn(){
  int prev_time=0;
  analogWrite(ENABLE_1, 250);
  analogWrite(ENABLE_2, 190);
  digitalWrite(MOTOR1_A , LOW);
  digitalWrite(MOTOR1_B , HIGH);
  digitalWrite(MOTOR2_A , HIGH);
  digitalWrite(MOTOR2_B , LOW);
  int current_time=millis();
  if(current_time -prev_time == right_delay){
    digitalWrite(MOTOR1_A , LOW);
    digitalWrite(MOTOR1_B , LOW);
    digitalWrite(MOTOR2_A , LOW);
    digitalWrite(MOTOR2_B , LOW);
    delay(800);
  }
  prev_time=current_time;
}

void straight(){
  int prev_time = 0;
  analogWrite(ENABLE_1, 200);
  analogWrite(ENABLE_2, 200);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , HIGH);
  digitalWrite(MOTOR2_B , LOW);
  if(distance1_cm < distance2_cm){  
    direction(210,190);// speed change
  }
  else if(distance1_cm > distance2_cm){
    direction(190,210);// speed change 
  }
  int current_time1 = millis();
  if(current_time1 - prev_time == straight_time){
    digitalWrite(MOTOR1_A , LOW);
    digitalWrite(MOTOR1_B , LOW);
    digitalWrite(MOTOR2_A , LOW);
    digitalWrite(MOTOR2_B , LOW);
    value1 = digitalRead(ir1);
    value2 = digitalRead(ir2);
    value3 = digitalRead(ir3);
    value4 = digitalRead(ir4);
    delay(100);
  }
  prev_time= current_time1;
}

void u_turn(){
  int prev_time = 0;
  analogWrite(ENABLE_1, 200);
  analogWrite(ENABLE_2, 200);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , LOW);
  digitalWrite(MOTOR2_B , HIGH);
  int current_time=millis();
  if(current_time-prev_time == uturn_delay){
    digitalWrite(MOTOR1_A , LOW);
    digitalWrite(MOTOR1_B , LOW);
    digitalWrite(MOTOR2_A , LOW);
    digitalWrite(MOTOR2_B , LOW);
    delay(800);
  }
  prev_time = current_time;
}

int ultrasonic(int trigpin,int echopin){
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  int duration = pulseIn(echopin, HIGH);// measure duration of pulse from ECHO pin
  int distance = (0.0343 * duration)/2; // calculate the distance
   Serial.print("distance1: ");
  Serial.print(distance1_cm);
  Serial.println(" cm");
  Serial.print("distance1: ");
  Serial.print(distance2_cm);
  Serial.println(" cm");
  delay(500);
  return distance;
}

void stop(){
  analogWrite(ENABLE_1, 0);
  analogWrite(ENABLE_2, 0);
  digitalWrite(MOTOR1_A , LOW);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , LOW);
  digitalWrite(MOTOR2_B , LOW);
}

void motor_init(int motorA,int motorB,int enable) {
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, LOW);
  analogWrite(enable, LOW);
}

void setup(){
Serial.begin (115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  motor_init(MOTOR1_A,MOTOR1_B,ENABLE_1);
  motor_init(MOTOR2_A,MOTOR2_B,ENABLE_2);
}

void loop(){
  value1 = digitalRead(ir1);
  value2 = digitalRead(ir2);
  value3 = digitalRead(ir3);
  value4 = digitalRead(ir4);
  distance1_cm = ultrasonic(trigPin1,echoPin1);// distance from left wall
  distance2_cm = ultrasonic(trigPin2,echoPin2);// distance for right wall
  if(!value1 && !value2){
    if(!value3 && value4){
      left_turn();// 90 degree rotation for turning left
      straight();
    } 
    else if(value3 && !value4){
      right_turn();// rotation towards right
      straight();
    }
    else if(!value1 && !value2 && !value3 && !value4){
      stop();
    }
  }
  else if(value1 && value2){
    if(!value3 && value4){
      left_turn();// 90 degree rotation for turning left
      straight();
    } 
    else if(!value3 && value4){
      right_turn();// rotation towards right
      straight();
    }
    else if(value3 && value4){
     u_turn();
     straight();
    }
  }
}



