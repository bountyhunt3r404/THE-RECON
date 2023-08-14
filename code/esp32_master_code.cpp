#include "Arduino.h"
//#include <SPI.h>

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200);
}

void loop() {
  //read from port 1, send to port 0:
  Serial2.print('S');

  if (Serial2.available()) {
    
    int inByte = Serial2.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial2.write(inByte);
  }
}