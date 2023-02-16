//Include the library files
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#define DHTTYPE DHT11 

uint8_t DHTPin = 4; 

DHT dht(DHTPin, DHTTYPE);  

// Enter your Auth token
char auth[] = "bfwLMLd0O6d4QchFnBnM62fFbLbiOvEk";

//Enter your WIFI SSID and password
char ssid[] = "Bowman";
char pass[] = "Michael1";

float Temperature;
float Humidity;

int sensorVal; 


void setup(){
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

   Serial.println("Connecting to ");
  Serial.println(ssid);


pinMode(DHTPin, INPUT);
  dht.begin();  

}
 
void loop(){
 Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
 Blynk.run();
Blynk.virtualWrite(V1, Temperature);
Blynk.virtualWrite(V5, Humidity);
}