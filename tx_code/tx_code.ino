char x[10];
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.readBytes(x,3);
  Serial.println(x);
  delay(100);
}