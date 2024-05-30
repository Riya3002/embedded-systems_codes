int enablePin1 = 6;
int enablePin2 = 7;
int inputPin1 = 2;
int inputPin2 = 3;

void setup() {
  // Set motor control pins as outputs
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  
  // Initialize motor to stop
  digitalWrite(enablePin1, LOW);
  digitalWrite(enablePin2, LOW);
  digitalWrite(inputPin1, LOW);
  digitalWrite(inputPin2, LOW);
}

void loop() {
  // Turn on the fan
  fanControl(true);
  delay(5000); // Run for 5 seconds
  
  // Turn off the fan
  // fanControl(false);
  // delay(5000); // Wait for 5 seconds
}

void fanControl(bool on) {
  if (on) {
    // Enable motor
    digitalWrite(enablePin1, HIGH);
    digitalWrite(enablePin2, HIGH);
    // Set motor direction
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, HIGH);
  } else {
    // Disable motor
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
  }
}