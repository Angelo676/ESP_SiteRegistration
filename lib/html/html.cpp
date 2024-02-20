#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

float h;
float t;
float f;




ESP8266WebServer server (80);

const char* ssid = "Angelo";
const char* password = "12345678";
const int ledPin = D5;

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


String userData[4];
void handleRootPath(){
  String html ="<html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>";
    html +="body { font-family: Arial, sans-serif; background-color: #d7e1e9; }";
    html +="input[type=text] {width: 100%; padding: 12px 20px; margin: 8px 0; display: inline-block; border: 1px solid #000000; border-radius: 4px; box-sizing: border-box;}" ;
    html +="button { width: 100%; background-color: #000000; color: white; padding: 14px 20px; margin: 8px 0;border: none; border-radius: 4px; cursor: pointer; } ";
    html +="</style></head><body>";



    html +="<h1> Quiz </h1>";
    html +="</br>";  


    html +="<form action=\"/submit\"method=\"get\">";
    html +="Surname: <input type=\"text\" name=\"surname\"><br>";
    html +="Name:<input type=\"text\" name=\"name\"><br>";


    html +="Email: <input type=\"text\" name=\"email\"><br>";
    html +="Date of Birth: <input type=\"date\" \"value\"=\"2003-12-17\" name=\"date\"><br>";
    html +="<button type=\"submit\" value=\"Submit\">Send</button>";
    html +="</form>";

    html +="<form action=\"/show\" method=\"get\">";
    html +="<button>Show All Data</button>";
    html +=" </form>";

    html +="<p>Temp:"+ String(t) +"°C<p><br>";
    html +="<p>Hum:"+ String(h) +"%<p><br>";


    html +="</body></html>";

  server.send(200, "text/html", html);

}


void setup(){
server.on("/",HTTP_GET, handleRootPath);
}