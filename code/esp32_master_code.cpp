#include "Arduino.h"
//#include <SPI.h>
#include <ArduinoJson.h>

// JSON Doc



void setup() {

  Serial.begin(9600);
  Serial2.begin(9600);
  // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  pinMode(BUILTIN_LED, OUTPUT);

  while (!Serial) continue;

}


void loop() {
  // Check if the other Arduino is transmitting
  if (Serial2.available()) 
  {
    // Allocate the JSON document
    // This one must be bigger than the sender's because it must store the strings
    StaticJsonDocument<300> doc;

    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(doc, Serial2);

    if (err == DeserializationError::Ok)
    {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.print("timestamp = ");
      Serial.println(doc["timestamp"].as<long>());
      Serial.print("value = ");
      Serial.println(doc["value"].as<int>());
    } 
    else 
    {
      // Print error to the "debug" serial port
      digitalWrite(BUILTIN_LED, LOW);
      //Serial.print("deserializeJson() returned ");
      //Serial.println(err.c_str());
  
      // Flush all bytes in the "link" serial port buffer
      while (Serial.available() > 0)
        Serial2.read();
    }
  }
}
