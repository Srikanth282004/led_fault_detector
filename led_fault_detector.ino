#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>


AsyncWebServer server(80);

const char* ssid = "Srikanth";          
const char* password = "srikanth";  

const int ledPin = 12;
const int ldrPin = A0;

void message(uint8_t *data, size_t len){
  WebSerial.println("Data Received!");
  String Data = "";
  for(int i=0; i < len; i++){
    Data += char(data[i]);
  }
  WebSerial.println(Data);
  if (Data == "ON"){
    digitalWrite(ledPin, HIGH);
  }
  if (Data=="OFF"){
    digitalWrite(ledPin, LOW);
  }
}
void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  WebSerial.begin(&server);
  WebSerial.msgCallback(message);
  server.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  int ldrStatus = analogRead(ldrPin);
  
  if (ldrStatus <= 300 && digitalRead(ledPin) == HIGH) {
    Serial.println("LED is ON");
    WebSerial.println("LED is ON"); 
    delay(5000);
  }
  else if (ldrStatus > 300 && digitalRead(ledPin) == HIGH) {
    Serial.println("LED REPAIR");
    WebSerial.println("LED REPAIR");
    delay(5000);
  }
  else {
    Serial.println("LED OFF");
    WebSerial.println("LED OFF");
    delay(5000);
  }
}
