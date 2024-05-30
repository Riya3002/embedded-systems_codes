#include <WiFi.h>

const char* ssid = "esp32";
const char* password = "12345678";
WiFiServer server(80); // Use the appropriate port number

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  Serial.print("Access point IP address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.print("Data received: ");
        Serial.println(data);
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}


