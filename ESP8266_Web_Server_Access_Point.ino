#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress local_ip(192,168,10,1);
IPAddress gateway(192,168,10,254);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

const char Main_page[] = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    
    <a href="biruon"> <button> LED Biru ON </button> </a>
    <a href="biruoff"> <button> LED Biru OFF </button> </a>

    <br>

    <a href="merahon"> <button> LED Merah ON </button> </a>
    <a href="merahoff"> <button> LED Merah OFF </button> </a>

</body>
</html>
)=====";

void website(){
  String web = Main_page;
  server.send(200, "text/html", web);
}

void biruon(){
  digitalWrite(D1, HIGH);
  website();
}

void biruoff(){
  digitalWrite(D1, LOW);
  website();
}

void merahon(){
  digitalWrite(D2, HIGH);
  website();
}

void merahoff(){
  digitalWrite(D2, LOW);
  website();
}

void setup() {
  pinMode(D1, OUTPUT); // LED BIRU
  pinMode(D2, OUTPUT); // LED MERAH
  
  // put your setup code here, to run once:
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP("Wifi Rumah", "12345678");

  server.on("/", website);
  server.on("/biruon", biruon);
  server.on("/biruoff", biruoff);
  server.on("/merahon", merahon);
  server.on("/merahoff", merahoff);
  
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
