#include <stdlib.h>
#include <time.h>
#include <WiFi.h>

const char* ssid = "ESP32_AP";
const char* password = "12345678";
const char* host = "192.168.4.1";  // IP address of the access point
String data1;
String data2;
String data3;
String data4;
String data5;
String data6;

WiFiClient client;

int Switch1 = 32;
//int ActPin1;       // Thumb
//int ActPin2;       // Middle & Index Finger
//int ActPin3;       // Ring & Last Finger
int buttonState1old = 0;

void gen_arr(int first, int last, int size, int arr[]) {
  arr[0] = first;
  arr[size - 1] = last;
  int diff = last - first;
  int i;
  for (i = 1; i < size - 1; i++) {
    arr[i] = first + (diff * i) / (size - 1);
  }
}

int random(int array[], int size) {
  int random_number = rand() % size;
  return array[random_number];
}

void fo() {
  int size1 = 15;
  int array1[size1];
  gen_arr(45, 60, size1, array1);
  srand(time(NULL));
  int rand1 = random(array1, size1);

  // Serial.print("\n TO:");
   Serial.println(rand1);
  //

  int size2 = 10;
  int array2[size2];
  gen_arr(30, 40, size2, array2);
  srand(time(NULL));
  int rand2 = random(array2, size2);
  

  //  String data1 = rand2;
  //  Serial.print("\n MIO:");
    Serial.println(rand2);
  //   analogWrite(ActPin2,rand2);
  int size3 = 10;
  int array3[size3];
  gen_arr(40, 50, size3, array3);
  srand(time(NULL));
  int rand3 = random(array3, size3);
  Serial.println(rand3);
   data1 = String(rand1);
   data2 = String(rand2);
   data3 = String(rand3);
  // sendDataToAccessPoint(data1);
  // // sendDataToAccessPoint(data2);
  // sendDataToAccessPoint(data3);


  //  String data3 = rand3;
  //  Serial.print("\n RLO:");
    
  //  analogWrite(ActPin3, rand3);
}

void fc() {
  int size1 = 20;
  int array1[size1];
  gen_arr(100, 120, size1, array1);
  srand(time(NULL));
  int rand1 = random(array1, size1);
 

  //  Serial.print("TC:");
    Serial.println(rand1);
  //  analogWrite(ActPin1, rand1);
  int size2 = 10;
  int array2[size2];
  gen_arr(70, 80, size2, array2);
  srand(time(NULL));
  int rand2 = random(array2, size2);


  //  Serial.print("MIC:");
    Serial.println(rand2);
  // analogWrite(ActPin2, rand2);
  int size3 = 15;
  int array3[size3];
  gen_arr(75, 90, size3, array3);
  srand(time(NULL));
  int rand3 = random(array3, size3);  
  Serial.println(rand3);
  data4 = String(rand1);
   data5 = String(rand2);
   data6 = String(rand3);
  
  // sendDataToAccessPoint(data1);
  
  // sendDataToAccessPoint(data2);
  
  // sendDataToAccessPoint(data3);

}

//  Serial.print("RLC:");
//  Serial.println(rand3);
// analogWrite(ActPin3, rand3);




void sendDataToAccessPoint(String data) {
 

  if (!client.connect(host, 80)) {
      Serial.println("Connection to access point failed");
      return;
    }
  if (client.connect(host, 80)) {
    // Send integer data to the access point
    client.print(data);
    client.flush();
    client.print("datasent ");
    client.stop();
    
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
    ;
  pinMode(Switch1, INPUT);
  //  pinMode(ActPin1, OUTPUT);
  //  pinMode(ActPin2, OUTPUT);
  //  pinMode(ActPin3, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(2000);
}

void loop() {
  int buttonstate1new = digitalRead(Switch1);
  
  if (client.connect(host, 80)) {  // Use the appropriate port number

    if (buttonState1old == 1 && buttonstate1new == 0) {
      fo();
      sendDataToAccessPoint(data1);
     sendDataToAccessPoint(data2);
      sendDataToAccessPoint(data3);;
    } else if (buttonState1old == 0 && buttonstate1new == 1) {
      fc();
      sendDataToAccessPoint(data4);
      sendDataToAccessPoint(data5);
      sendDataToAccessPoint(data6);
    }
    // client.stop();
    buttonState1old = buttonstate1new;
  } else {
    Serial.println("Connection failed");
  }
  

  delay(100);
}