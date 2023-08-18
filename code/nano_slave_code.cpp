/*
          MADE BY BOUNTY
    THIS CODE IS FOR ARDUINO NANO
          
*/

#include <Arduino.h>

#include <ArduinoJson.h>
#include <Joystick.h>
#include <AxisJoystick.h>
//#include <RF24.h>
#include <SPI.h>

// Pin assingments

//Joysticks
//LEFT
#define L_X A1
#define L_Y A0
#define L_PIN 4

//RIGHT
#define R_X A6
#define R_Y A7
#define R_PIN 7

//POTS
#define L_POT A2
#define R_POT A3

//Triggers
#define L_Trig 5
#define R_Trig 6

//Axis JoyStick
AxisJoystick LJOY(L_PIN, L_X, L_Y);  //Left Joystick
AxisJoystick RJOY(R_PIN, R_X, R_Y);  //Right Joystick


void Json_Serial_Communication() {
    // Values we want to transmit
  long timestamp = millis();
  int value = analogRead(1);

  // Print the values on the "debug" serial port
  Serial.print("timestamp = ");
  Serial.println(timestamp);
  Serial.print("value = ");
  Serial.println(value);
  Serial.println("---");

  // Create the JSON document
  StaticJsonDocument<200> doc;
  doc["timestamp"] = timestamp;
  doc["value"] = value;

  // Send the JSON document over the "link" serial port
  serializeJson(doc, Serial);

  // Wait
  delay(1000);
}

String moveTitle(const Joystick::Move move) {
        switch (move) {
            case Joystick::Move::NOT:
            return "NOT";
            case Joystick::Move::PRESS:
            return "PRESS";
            case Joystick::Move::UP:
            return "UP";
            case Joystick::Move::DOWN:
            return "DOWN";
            case Joystick::Move::RIGHT:
            return "RIGHT";
            case Joystick::Move::LEFT:
            return "LEFT";
            default:
            return "???";
        }
    }


/**
 * @brief Transmit the readings from all the sensors to ESP32 over serial
 *        using JSON format
 * 
 */
void json_over_serial_communication() {
    //Creating JSON Document to store the sensor readings
    StaticJsonDocument<500> sensordata;

    //Default JSON doc structure
    sensordata["L_JOY_SINGLEREAD"] = moveTitle(LJOY.singleRead());
    sensordata["L_JOY_MULTIPLEREAD"] = moveTitle(LJOY.multipleRead());
    sensordata["R_JOY_SINGLEREAD"] = moveTitle(RJOY.singleRead());
    sensordata["R_JOY_MULTIPLEREAD"] = moveTitle(RJOY.multipleRead());

    serializeJson(sensordata, Serial);
}

    

void setup() {
    /*
    pinMode(L_X, INPUT);
    pinMode(L_Y, INPUT);
    pinMode(L_PIN, INPUT_PULLUP);
    pinMode(R_X, INPUT);
    pinMode(R_Y, INPUT);
    pinMode(R_PIN, INPUT_PULLUP);
    pinMode(L_POT, INPUT);
    pinMode(R_POT, INPUT);
    */
    pinMode(L_Trig, INPUT_PULLUP);
    pinMode(R_Trig, INPUT_PULLUP);  

    //Calibration
    LJOY.calibrate(0, 1022, 100);
    RJOY.calibrate(0, 1022, 100);
    
    Serial.begin(9600);
    while (!Serial) continue;
}

void loop() {
    //ReadSense();
    //PrintFunc();
    //SerialCommunication();
    //Json_Serial_Communication();
    json_over_serial_communication();
}