int pins[8]= {0,1,2,3,4,8,9,10};
void setup()
{
  for(int j=0;j<=7;j++){
  pinMode(pins[j], OUTPUT);
    
  }
  
}

void loop()
{
  //for 0
   digitalWrite(9, 1);
  digitalWrite(8,1);
  digitalWrite(4,1);
  digitalWrite(1,1);
  digitalWrite(2,1);
  digitalWrite(0,1);
  //for 1
  
  // for 2
  digitalWrite(9, 1);
  digitalWrite(8,1);
  digitalWrite(4,1);
  digitalWrite(1,1);
  digitalWrite(2,1);
  digitalWrite(0,1);
}