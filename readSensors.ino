#include <Wire.h>
#include "SPI.h" //Why? Because library supports SPI and I2C connection
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP280.h"
#include <SoftwareSerial.h>

//Setup connection of the sensor
Adafruit_BMP280 bmp; // I2C

SoftwareSerial BTserial(10, 11);

//Variables
float pressure;    //To store the barometric pressure (Pa)
float temperature;  //To store the temperature (oC)

int lightSensorPin = A0; // select the input pin for LDR

int lightSensorValue = 0; // variable to store the value coming from the sensor

void setup() {
  BTserial.begin(9600);
  bmp.begin();    //Begin the sensor
    Serial.begin(9600); //Begin serial communication at 9600bps
    Serial.println("Adafruit BMP280 test:");
}

void loop() {

  
  //Read values from the sensor:
  pressure = bmp.readPressure();
  temperature = bmp.readTemperature();
  
  //Print values to serial monitor:
   lightSensorValue = analogRead(lightSensorPin); // read the value from the light sensor

    BTserial.print(pressure/100);
    BTserial.print(",");
    //BTserial.print("\t");
    BTserial.print(temperature);
    BTserial.print(",");
    //BTserial.println();
    BTserial.println(lightSensorValue);
    BTserial.print(";");
    
    delay(1000); //Update every 1 sec
}
