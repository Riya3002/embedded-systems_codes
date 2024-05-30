  
int TA[7] = {2,3,4,5,6,7,8};// Tranfer Pins Array
//int ActPin1;       // Thumb
//int ActPin2;       // Middle & Index Finger
//int ActPin3;       // Ring & Last Finger
const int buttonPin = 2;  
int buttonState = 0;
void sendData(int decimal) {
  
  int binary[7];
  int q, d=64;
  for (int i=0; i<7; i++) {
    binary[i] = decimal/d;
    decimal = decimal%d;
    d=d/2; 
  }
  for(int i=0; i<7; i++) {
    digitalWrite(TA[i], binary[i]);

    delay(100);
  }
}

void gen_arr(int first, int last, int size, int arr[])
{
  arr[0] = first;
  arr[size - 1] = last;
  int diff = last - first;
  int i;
  for (i = 1; i < size - 1; i++)
  {
    arr[i] = first + (diff * i) / (size - 1);
  }
}

int random_function(int array[], int size)
{
  // srand(time(NULL));
  int random_number = random() % size;
  return array[random_number];
}

void fo() {
  int size1 = 15;
  int array1[size1];
  gen_arr(45 , 60, size1, array1);
  int rand1 =  random_function(array1, size1);
  Serial.print(" TO:");
  Serial.println(rand1);
  sendData(rand1);
  delay(100);
//  analogWrite(ActPin1,rand1);
  int size2 = 10;
  int array2[size2];
  gen_arr(30, 40, size2, array2);
  int rand2 = random_function(array2, size2);
  Serial.print(" MIO:");
  Serial.println(rand2);
  sendData(rand2);
  delay(100);
//   analogWrite(ActPin2,rand2);
  int size3 = 10;
  int array3[size3];
  gen_arr(40, 50, size3, array3);

  int rand3 = random_function(array3, size3);
  Serial.print(" RLO:");
  Serial.println(rand3);
  sendData(rand3);
  delay(100);
//  analogWrite(ActPin3,rand3);
  // sendData(0);
}

void fc() {
   int size1 = 20;
  int array1[size1];
  gen_arr(100 , 120, size1, array1);

  int rand1 =  random_function(array1, size1);
  Serial.print("TC:");
  Serial.println(rand1);
  sendData(rand1);
  delay(100);
//  analogWrite(ActPin1,rand1);
  int size2 = 10;
  int array2[size2];
  gen_arr(70, 80, size2, array2);

  int rand2 =  random_function(array2, size2);
  Serial.print("MIC:");
  Serial.println(rand2);
  sendData(rand2);
  delay(100);
//  analogWrite(ActPin2,rand2);
  int size3 = 15;
  int array3[size3];
  gen_arr(75, 90, size3, array3);

  int rand3 =  random_function(array3, size3);
  Serial.print("RLC:");
  Serial.println(rand3);
  sendData(rand3);
  delay(100);
//   analogWrite(ActPin3,rand3);
  
  // sendData(0);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  for(int i=0; i<7; i++) {
    pinMode(TA[i], OUTPUT);
  }
  randomSeed(analogRead(0));
  
}
  
void loop()
{
   buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    fc();
  } 
  else {
    fo();
  }
}







