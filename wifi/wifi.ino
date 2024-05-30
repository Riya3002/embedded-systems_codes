#include <WiFi.h>

const char* ssid = "Riya";
const char* password = "87654321";

void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Your code here
}