#include <WiFi.h>

const char* ssid = "esp32";
const char* password = "12345678";
const char* host = "192.168.4.1";  // IP address of the access point

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(2000); // Wait for the access point to start up
}

void loop() {
  if (!client.connected()) {
    if (client.connect(host, 80)) 
    { // Use the appropriate port number
      String data = "Helloooooo, ESP32 access point!";
      client.println(data);
      Serial.println("Data sent");
      client.stop();
    } 
    else 
    {
      Serial.println("Connection failed");
    }
  }

  delay(5000);
}