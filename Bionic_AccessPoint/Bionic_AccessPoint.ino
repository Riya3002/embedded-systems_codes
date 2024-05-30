#include <WiFi.h>

const char* ssid = "ESP32_AP";
const char* password = "12345678";
WiFiServer server(80); // Use the appropriate port number

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);

  Serial.print("Access point IP address: ");
  Serial.println(WiFi.softAPIP());


  server.begin();
}

// void loop() {
//   WiFiClient client = server.available();
//   if (client) {
//     Serial.println("New client connected");
//     while (client.connected()) {
//       if (client.available()) {
//         String data = client.readStringUntil('\n');
//         Serial.print("Data received: ");
//         Serial.println(data);
//       }
//     }
//     client.stop();
//     Serial.println("Client disconnected");
//   }

//   // Your code here
// }

void loop() {
  WiFiClient client = server.available();

  if (client) {
    
    // Serial.print("Number of connections:");
    // Serial.println(WiFi.softAPgetStationNum());
    while (client.connected()) {
      if (client.available()) {
        // Read data from the client
        String data = client.readStringUntil('\n');

        // Convert the received string to an integer
         int receivedData = data.toInt();

        // Print the received integer data on the serial monitor
        Serial.println(data);
      }
    }

    // client.stop();
    // Serial.println("Client disconnected");
  }
}