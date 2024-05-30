int TA[7] = {15,2,0,4,16,17,5}; // Tranfer Pins Array

int b2d(int* bin) {
  int dec=0, m=1, d=64;
  for (int i=0; i<7; i++) {
    m=1;
    for (int j=6; j>i; j--) {
      m=m*2;
    }
    dec = dec + bin[i]*m;
  }
   return dec;
}

void setup() {
  Serial.begin(9600);
 for(int i=0; i<7; i++) {
   pinMode(TA[i], INPUT);
 }
//  pinMode(TA0, INPUT);
//   pinMode(TA1, INPUT);
//   pinMode(TA2, INPUT);
//   pinMode(TA3, INPUT);
//   pinMode(TA4, INPUT);
//   pinMode(TA5, INPUT);
//   pinMode(TA6, INPUT);
}

void loop() {
  int binary[7];
      for(int i=0; i<7; i++) {
         binary[i] = digitalRead(TA[i]);
 }
    // binary[0] = digitalRead(TA0);
    // binary[1] = digitalRead(TA1);
    // binary[2] = digitalRead(TA2);
    // binary[3] = digitalRead(TA3);
    // binary[4] = digitalRead(TA4);
    // binary[5] = digitalRead(TA5);
    // binary[6] = digitalRead(TA6);
 

   int value = b2d(binary);
   Serial.println(value);
  delay(500);
}