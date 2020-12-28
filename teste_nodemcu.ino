#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "BLACKOUT";
const char* password = "marinh@123";
ESP8266WebServer server(80);
String page = "";
int LEDPin = 13;

// Set your Static IP address
IPAddress local_IP(172, 16, 100, 54);
// Set your Gateway IP address
IPAddress gateway(172, 16, 100, 52);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  // put your setup code here, to run once:
  page = "<h1>Desligamento Remoto RECIM</h1><p><a href=\"TURNOn\"><button>OFF</button></a>&nbsp;<a href=\"TURNOff\"><button>ON</button></a></p>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
   
  delay(1000);
  Serial.begin(115200);

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
 server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/TURNOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/TURNOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  server.handleClient();
}
