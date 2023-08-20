#include <Arduino.h>
//#include <SPI.h>
#include <ArduinoJson.h>

// JSON Doc



void setup() {

  Serial.begin(115200);
  Serial2.begin(115200);
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
    StaticJsonDocument<500> sensordata;

    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(sensordata, Serial2);

    if (err == DeserializationError::Ok)
    {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.print("| LJOY_SINGLE_READ: ");
      Serial.print(sensordata["L_JOY_SINGLEREAD"].as<String>());
      Serial.print("| LJOY_MULTIPLE_READ: ");
      Serial.print(sensordata["L_JOY_MULTIPLEREAD"].as<String>());
      Serial.print("| RJOY_SINGLE_READ: ");
      Serial.print(sensordata["R_JOY_SINGLEREAD"].as<String>());
      Serial.print("| RJOY_MULTIPLE_READ: ");
      Serial.print(sensordata["R_JOY_MULTIPLEREAD"].as<String>());
      Serial.print("| L_TRIG: ");
      Serial.print(sensordata["L_TRIG"].as<bool>());
      Serial.print("| R_TRIG: ");
      Serial.print(sensordata["R_TRIG"].as<bool>());
      Serial.println(" |");
      digitalWrite(BUILTIN_LED, LOW);
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
