
#include <WiFi.h>
#include<ESP32Servo.h>
Servo myservo;
#define MotorPin1 18
const char* ssid     = "Pranav's Phone";
const char* password = "1234567890";
int mode; 
float angle=0;

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    myservo.attach(MotorPin1);
   
    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients
 switch(mode) {
        case 1:
        if (angle<=180) {
          angle+=0.1;
          delay(1);
        }
          break;
        case 2:
        if (angle>=0) {
          angle-=0.1;
          delay(1);
        }
          break;
        case 3:
          break;
      }
      myservo.write(angle);

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print(" <head><style>button{font-size:50px ;padding:10px 10px color:black; backgroundcolor:cyan;} button:hover{color:red; background-color:yellow;}  </style></head>");
            client.print(" <div><center>welcome to servo motor control system</center></div>");
            client.print(" <a href=\"/C\"><button> clockwise rotation</button></a><br>");
            client.print(" <a href=\"/A\"><button> anticlockwise rotation</button></a><br>");
            client.print(" <a href=\"/S\"><button> stop rotation</button></a><br>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /c" or "GET /A" or "GET /S":
        if (currentLine.endsWith("GET /C")) {
            mode=1;            
        }
        if (currentLine.endsWith("GET /A")) {
            mode=2;          
        }
         if (currentLine.endsWith("GET /S")) {
            mode=3;             
        }
      }
      
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
