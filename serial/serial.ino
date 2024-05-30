// int TA0 = 15;
// int TA1 = 2;
// int TA2 = 0;
// int TA3 = 4;
// int TA4 = 16;
// int TA5 = 17;
// int TA6 = 5;
int TA[7] = {13,12,14,27,26,25,33};// Tranfer Pins Array
int value;

void d2b(int dec, int* bin) {
  int q, d=64;
  for (int i=0; i<7; i++) {
    bin[i] = dec/d;
    dec = dec%d;
    d=d/2; 
  }
  // Serial.println(bin[7]);
}

void setup() {
  Serial.begin(9600);
  for(int i=0; i<7; i++) {
    pinMode(TA[i], OUTPUT);
  }

}

void loop() {
  while (Serial.available()>0) {
    value = Serial.read();
    int binary[7];
    d2b(value, binary);
    for(int i=0; i<7; i++) {
      Serial.println(binary[i]);
    }
      for(int i=0; i<7; i++) {
        digitalWrite(TA[i], binary[i]);
      }
     
    
  }
  delay(500);
}