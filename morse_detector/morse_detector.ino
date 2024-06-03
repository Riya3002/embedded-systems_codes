#define morse_delay 400               // TIme after signal is classified as '_'
#define buttonPin 5                   // Get morse input
#define RED 11                        // Blinks on '_' signal
#define BLUE 12                       // Blinks on '.' signal
int SSD[] = {8, 7, 2, 3, 4, 9, 10};   // [a, b, c, d, e, f, g]
int prev_time = 0, current_time = 0;
int counter = 0;
bool prev_state = 0, current_state = 0;
bool bin_morse[] = {0,0,0};

void setup() {
  pinMode(buttonPin,INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  for (int i = 0; i<7; i++) {
    pinMode(SSD[i], OUTPUT);
  }
  Serial.begin(9600);
}

int chars[8][7] = {
  {1,1,1,0,1,1,1},
  {1,1,1,1,1,1,1},
  {1,0,0,1,1,1,0},
  {1,1,1,1,1,1,0},
  {1,0,0,1,1,1,1},
  {1,0,0,0,1,1,1},
  {1,1,1,1,1,1,0},
  {0,1,1,0,1,1,1}
};

void convert(bool arr[]) {
  int num = 0;
  int mul = 1;
  for (int i=2; i>=0; i--) {
    if (arr[i]) num+=mul;
    mul *= 2;
  }
  for (int i=0; i<7; i++) {
    digitalWrite(SSD[i], chars[num][i]);
  }
  delay(500);
  for (int i=0; i<7; i++) {
    digitalWrite(SSD[i], LOW);
  }
}

void loop() {
  if (counter == 3) {
    convert(bin_morse);
    counter = 0;
    bin_morse[0], bin_morse[1], bin_morse[2] = 0,0,0;
  }
  current_state = digitalRead(buttonPin);
  digitalWrite(LED_BUILTIN, current_state);
  digitalWrite(RED,LOW);
  digitalWrite(BLUE,LOW);

  if(current_state != prev_state) {
    prev_time = current_time;
    current_time = millis();
    if (!current_state) {
      if(current_time - prev_time >= morse_delay){
          bin_morse[counter] = 1;
          digitalWrite(RED,HIGH);
          delay(100);
          digitalWrite(RED,LOW);
        } else {
          bin_morse[counter] = 0;
          digitalWrite(BLUE,HIGH);
          delay(100);
          digitalWrite(BLUE,LOW);
      }
      counter++;
    }
  }
  prev_state = current_state;
}
