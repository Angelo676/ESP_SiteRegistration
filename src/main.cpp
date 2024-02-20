#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

unsigned long interval=3000;
unsigned long previousMillis=0;

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

void handleSubmit(){
userData[0]=server.arg("surname");
userData[1]=server.arg("name");
userData[2]=server.arg("email");
userData[3]=server.arg("date");
server.sendHeader("Location", "/");
server.send(302, "text/plain", "Data submitted successfully");

}

void handleShow(){
Serial.println(". . . . . . . . . . . . . . . . .");
Serial.println("User surname: "+ userData[0]);
Serial.println("User name: "+ userData[1]);
Serial.println("User email: "+ userData[2]);
Serial.println("User date of birth: "+ userData[3]);
Serial.println(". . . . . . . . . . . . . . . . .");
server.sendHeader("Location", "/");
server.send(302, "text/hider", "Data showed successfully");
}



void setup() {
dht.begin();
Serial.begin (9600);
pinMode(D5, OUTPUT);

// WiFi.mode(WIFI_STA); // AP - acess point; STA - station mode

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED){
  delay (1000);
  Serial.print ( "." );
}
Serial.println("I got connected");
Serial.println(WiFi.localIP());





server.on("/",HTTP_GET, handleRootPath);
server.on("/submit",HTTP_GET, handleSubmit);
server.on("/show",HTTP_GET, handleShow);


server.begin();
Serial.println("Server is ready");



}

void loop() {
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
h = dht.readHumidity();
t = dht.readTemperature();
f = dht.readTemperature();






  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
previousMillis = millis();
}
server.handleClient();

}


