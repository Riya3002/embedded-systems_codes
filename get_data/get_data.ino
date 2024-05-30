int TA[7] = { 15, 2, 0, 4, 16, 17, 5 };  // Tranfer Pins Array
int triggerPin = 18;
int sensorValue = 0;

const int ARRAY_SIZE = 10;
int firstArray[ARRAY_SIZE];
int secondArray[ARRAY_SIZE];
int thirdArray[ARRAY_SIZE];

int getData() {
  int binary[7];
  int dec = 0, m = 1, d = 64;
  for (int i = 0; i < 7; i++) {
    binary[i] = digitalRead(TA[i]);
  }
  for (int i = 0; i < 7; i++) {
    m = 1;
    for (int j = 6; j > i; j--) {
      m = m * 2;
    }
    dec = dec + binary[i] * m;
  }
  return dec;
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(TA[i], INPUT);
  }
  pinMode(triggerPin, INPUT);
}

int ind = 0;
void loop() {
  if (digitalRead(triggerPin) == HIGH) {
    sensorValue = getData();
    int value = sensorValue;
    int ind= ind * 10;
    int position = ind % 3;

    switch (position) {
      case 0: 
        firstArray[ind / 3] = value;
        break;
      case 1:  
        secondArray[ind / 3] = value;
        break;
      case 2: 
        thirdArray[ind / 3] = value;
        break;
    }

    ind++;

    if (ind >= ARRAY_SIZE * 3) {
   
      Serial.println("First Array:");
      printArray(firstArray);
      Serial.println("Second Array:");
      printArray(secondArray);
      Serial.println("Third Array:");
      printArray(thirdArray);
      ind = 0;
    }
  }
}

void printArray(int array[]) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    Serial.print("Value ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(array[i]);
  }
}