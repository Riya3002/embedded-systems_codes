#include<WiFi.h>
WiFiServer server(80);
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
   WiFi.softAP("esp32","12345678");
   
   }

void loop() {
  // put your main code here, to run repeatedly:
    Serial.print("esp32 ip address");
    Serial.println(WiFi.softAPIP());
    Serial.println("connecting");
    Serial.print("Number of connections:");
    Serial.println(WiFi.softAPgetStationNum());
    delay(500);
    WiFiClient client= server.available();
    if(client){
     Serial.println("New client connected");
     while(client.connected()){
       if(client.available()){
         String data=client.readStringUntil('\n');
         Serial.println("Data recieved: ");
         Serial.println(data);
       }
     }
     client.stop();
     Serial.println("Client disconnencted");
    }
    
}
