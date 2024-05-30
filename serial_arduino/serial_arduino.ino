int TA[7] = { 15, 2, 0, 4, 16, 17, 5 };  // Tranfer Pins Array
int valueOld = 0;
int value = 0;

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
}

void loop() {
  value = getData();
  if (value != valueOld) {
    if (value>=70 && value<=120) {
      Serial.println(value);
    }
    else {
      Serial.println("error");
    }
  }
  valueOld = value;
}
