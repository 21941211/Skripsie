/*
  Adapted from WriteSingleField Example from ThingSpeak Library (Mathworks)
  
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"
#define DHTTYPE DHT11

const char* ssid = "Bowman";   // your network SSID (name) 
const char* password = "Michael1";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "VDKKK09SIHAK5RU7";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

uint8_t DHTPin = 4; 

DHT dht(DHTPin, DHTTYPE);  

// Variable to hold temperature readings
float temperatureC;
float humidity;
//uncomment if you want to get temperature in Fahrenheit



void setup() {
  Serial.begin(115200);  //Initialize serial
 pinMode(DHTPin, INPUT);
  dht.begin();  
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // Get a new temperature reading
    temperatureC = dht.readTemperature(); // Gets the values of the temperature
  humidity = dht.readHumidity(); // Gets the values of the humidity 
    Serial.print("Temperature (ºC): ");
    Serial.println(temperatureC);
    Serial.print("Humidity (%): ");
    Serial.println(humidity);
    

  
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);
    
    delay(3000);
    int y = ThingSpeak.writeField(myChannelNumber,2,humidity,myWriteAPIKey);
    delay(3000);
if(y == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    
    lastTime = millis();
  }
}