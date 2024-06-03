// Ultrasonic pins
int trigPin1 = PA8;    // TRIG pin for Ultrasonic1
int echoPin1 = PB8;    // ECHO pin for Ultrasonic1
int trigPin2 = PB1;    // TRIG pin for Ultrasonic2
int echoPin2 = PA0;    //ECHO pin for Ultrasonic2

// IR sensor pins 
int ir1 = PB11; // input pin for front-left IRsensor 
int ir2 = PB10; // input pin for front-right IRsensor
int ir3 = PA5; // input pin for left IRsensor
int ir4 = PA4; // input pin for right IRsensor
float duration1, distance1_cm;
float duration2, distance2_cm;

int switchPin = PA15;// main switch 
// Motor_1 Connection
#define ENABLE_1 PA9
#define MOTOR1_A PB14
#define MOTOR1_B PB15

// Motor_2 Connection
#define ENABLE_2 PA1
#define MOTOR2_A PA4
#define MOTOR2_B PA5
int motorspeed_1;// speed of motor1
int motorspeed_2;// speed OF MOTOR2

// function for obstacle sensing
int irsensor(int input){
  int value= digitalRead(input);
  if(value){  
    // Serial.println(input);
    return 1;
  }
  else{
    return 0;
  }
}

// function calculating distance with Ultrasonic sensor 
int ultrasonic(int trigpin,int echopin){
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  int duration = pulseIn(echopin, HIGH);        // measure duration of pulse from ECHO pin
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

void motor_init(int motor_A,int motor_B,int enable) {
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(motor_A, LOW);
  digitalWrite(motor_B, LOW);
  analogWrite(enable, LOW);
}
// function for rotation of motors taking speeds as parameters
void direction(int en1,int en2){
  analogWrite(ENABLE_1, en1);
  analogWrite(ENABLE_2, en2);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , HIGH);
  digitalWrite(MOTOR2_B , LOW);
}

void stop(){
  digitalWrite(MOTOR1_A , LOW);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , LOW);
  digitalWrite(MOTOR2_B , LOW);
}

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(switchPin,INPUT),
  motor_init(MOTOR1_A,MOTOR1_B,ENABLE_1);
  motor_init(MOTOR2_A,MOTOR2_B,ENABLE_2);
}
// code for forward motion
// void forward(){
//   analogWrite(ENABLE_1, 30);
//   analogWrite(ENABLE_2, 30);
//   digitalWrite(MOTOR1_A , HIGH);
//   digitalWrite(MOTOR1_B , LOW);
//   digitalWrite(MOTOR1_A , HIGH);
//   digitalWrite(MOTOR1_B , LOW);
// }
// // to rotate int left direction
// void left(){
//   analogWrite(ENABLE_1, 30);
//   analogWrite(ENABLE_2, 30);
//   digitalWrite(MOTOR1_A , HIGH);
//   digitalWrite(MOTOR1_B , LOW);
//   digitalWrite(MOTOR2_A , HIGH);
//   digitalWrite(MOTOR2_B , LOW);
// }
// // rotating in right direction
// void right(){
//   analogWrite(ENABLE_1, 30);
//   analogWrite(ENABLE_2, 30);
//   digitalWrite(MOTOR1_A , HIGH);
//   digitalWrite(MOTOR1_B , LOW);
//   digitalWrite(MOTOR2_A , HIGH);
//   digitalWrite(MOTOR2_B , LOW);
// }


void loop() {
  int move = digitalRead(switchPin);
  // generate 10-microsecond pulse to TRIG pin
  int value1= irsensor(ir1);
  int value2= irsensor(ir2);
  int value3= irsensor(ir3);
  int value4= irsensor(ir4);
  distance1_cm = ultrasonic(trigPin1,echoPin1);// distance from left wall
  distance2_cm = ultrasonic(trigPin1,echoPin1);// distance for right wall
  if(!value1 && !value2){
    if(value3 && value4){
      if(distance1_cm == distance2_cm){
        direction(30,30);
      }
      else if(distance1_cm < distance2_cm){
        direction(40,30);// speed change
      }
      else if(distance1_cm > distance2_cm){
        direction(30,40);// speed change 
      }
    }
    else if(!value3 && value4){
      direction(20,50);// 90 degree rotation for turning left
    } 
    else if(!value3 && value4){
      direction(50,20);// rotation towards right
    }
  }
  else if(value1 && value2){
    if(!value3 && value4){
      direction(20,50);// 90 degree rotation for turning left
    } 
    else if(!value3 && value4){
      direction(50,20);// rotation towards right
    }
    else if(value3 && value4){
      stop();
      direction(60,10);
    }
  } 
}



