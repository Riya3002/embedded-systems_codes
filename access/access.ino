#include<WiFi.h>
const char* ssid="esp32";
const char* password="12345678";
const char* host ="192.168.4.1";
WiFiClient client;
void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
    Serial.println("connecting to wifi");

  }
  Serial.println("Connected");
  Serial.println("ip address:");
  Serial.println(WiFi.localIP());
}
void loop(){
  if(!client.connected()){
    if(client.connect(host, 80)){
      String data =" hello";
      client.println(data);
      Serial.println("{'data sent");
      client.stop();
    
    }
    else{
      Serial.println("connection failed");
    }
  }
  delay(5000);
}