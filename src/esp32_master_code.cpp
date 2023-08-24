/*
          MADE BY BOUNTY
    THIS CODE IS FOR ESP-32

*/

#include <Arduino.h>
// #include <SPI.h>
#include <ArduinoJson.h>

/*
bool dataok() {
  DeserializationError err = deserializeJson(sensordata, Serial2);
  if (err == DeserializationError::Ok) {
    return true;
  }

  else {
    return false;
  }
}
*/

void setup()
{

  Serial.begin(115200);
  Serial2.begin(115200);
  // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  pinMode(BUILTIN_LED, OUTPUT);

  while (!Serial)
    continue;
}

void loop()
{
  // Check if the Arduino is transmitting

  StaticJsonDocument<500> sensordata;

  String input = Serial2.readStringUntil('\n');

  // Split input into data and checksum
  int index = input.lastIndexOf('@');
  String data = input.substring(0, index);
  String checksumStr = input.substring(index + 1);
  uint8_t checksum = (uint8_t)strtol(checksumStr.c_str(), NULL, HEX);

  // Verify checksum
  uint8_t calculatedChecksum = 0;
  for (int i = 0; i < data.length(); i++)
  {
    calculatedChecksum ^= data[i];
  }

  if (calculatedChecksum != checksum)
  {
    Serial.println("Checksum error!");
    return;
  }

  DeserializationError error = deserializeJson(sensordata, data);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

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
