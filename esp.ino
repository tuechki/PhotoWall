#include <ESP8266WiFi.h>
#include <MQTTClient.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

const char* ssid = "Ap.16";
const char* password = "19651965";

WiFiClient WiFiclient;
MQTTClient client;

Adafruit_BMP280 bme; // I2C

unsigned long lastMillis = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());

  delay(2000);

  Serial.print("connecting to MQTT broker...");
  client.begin("broker.shiftr.io", WiFiclient);
  connect();
  
  
  SerialBMP.begin(9600);
  SerialBMP.println(F("BMP280 test"));

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

}

void connect(){
  while(!client.connect("nodemcu", "try", "try")){
    Serial.print(".");
    }

   Serial.println("\nconnected!");
   client.subscribe("nodemcu");
    
}

void loop() {

  int temp = bme.readTemperature();

  int pressure = (bme.readPressure() / 100);

  int val = analogRead(A0);
  client.loop();
  if(!client.connected()){
    connect();
    }

  if(millis() - lastMillis > 1000){
      lastMillis = millis();
      client.publish("nodemcu/photocell", (String)val);
      client.publish("nodemcu/photocell", (String)temp);
      client.publish("nodemcu/photocell", (String)pressure);
      Serial.println("" + (String)val);
    }

}

//void messageReceived(String topic, String payload, char * bytes, unsigned int length){
//  Serial.print("incoming: ");
//  Serial.print(topic.c_str());
//  Serial.print("-");
//  Serial.print(payload.c_str());
//}
