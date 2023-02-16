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
char auth[] = "Uoz5hJjrFIchat78o3tT1-iQ6hIc-L4f";

//Enter your WIFI SSID and password
char ssid[] = "Bowman";
char pass[] = "Michael1";

float Temperature;
float Humidity;

int sensorVal; 
BlynkTimer timer; 

void myTimer() 
{
  // This function describes what will happen with each timer tick
  // e.g. writing sensor value to datastream V5
  Blynk.virtualWrite(V5, sensorVal);  
}


void setup(){
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

   Serial.println("Connecting to ");
  Serial.println(ssid);
timer.setInterval(1000L, myTimer); 

pinMode(DHTPin, INPUT);
  dht.begin();  

}
 
void loop(){
 Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  sensorVal = Temperature;
  Blynk.run();


timer.run();  
}