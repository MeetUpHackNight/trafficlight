#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define redLight D1
#define greenLight D2
const char* ssid = "xxx";
const char* password = "xxx";
ESP8266WebServer server(80);

void root() {
  server.send(200, "text/plain", "I am smart traffic light");
}

void success() {
  server.send(200, "text/plain", "Ligar");
  digitalWrite(redLight, LOW);
  digitalWrite(greenLight, HIGH); 
}

void failure() {
  server.send(200, "text/plain", "Desligar");
  digitalWrite(redLight, HIGH);
  digitalWrite(greenLight, LOW);
}

void notFound(){
  String msg = "File not found\n\n";
  msg += "URI: ";
  msg += server.uri();
  msg += "\nMethod: ";
  msg += (server.method() == HTTP_GET)?"GET":"POST";
  msg += "\nArguments: ";
  msg += server.args();
  msg += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    msg += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", msg);
}

void setup(){
  pinMode(redLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  digitalWrite(redLight, LOW);
  digitalWrite(greenLight, LOW);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println(".");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", root);
  server.on("/failure", failure);
  server.on("/success", success);
  server.onNotFound(notFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();
}