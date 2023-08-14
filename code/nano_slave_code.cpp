/*
          MADE BY BOUNTY
    THIS CODE IS FOR ARDUINO NANO
          
*/

#include <Arduino.h>

#include <RF24.h>
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

/* Variables for Storing Values of Various Sensors */
//Left JoyStick
int L_X_VAL = 0;
int L_Y_VAL = 0;
boolean L_PIN_STATE = false;

//Right JoyStick
int R_X_VAL = 0;
int R_Y_VAL = 0;
boolean R_PIN_STATE = false;

//Triggers
boolean L_Trig_STATE = false;
boolean R_Trig_STATE = false;

//Pots
int L_POT_VAL = 0;
int R_POT_VAL = 0;

//Funtion for reading sensor values
void ReadSense() {
    //All switches
    L_PIN_STATE = digitalRead(L_PIN);
    R_PIN_STATE = digitalRead(R_PIN);
    L_Trig_STATE = digitalRead(L_Trig);
    R_Trig_STATE = digitalRead(R_Trig);

    //All Joysticks and Pots
    L_X_VAL = map(analogRead(L_X), 0, 1023, 0, 255);
    L_Y_VAL = map(analogRead(L_Y), 0, 1023, 0, 255);
    R_X_VAL = map(analogRead(R_X), 0, 1023, 0, 255);
    R_Y_VAL = map(analogRead(R_Y), 0, 1023, 0, 255);
    L_POT_VAL = analogRead(L_POT);
    R_POT_VAL = analogRead(R_POT);
}

//For Debugging
void PrintFunc() {
    if (Serial.available() > 0) {
    while (Serial.available() > 0) {
     Serial.print(L_X_VAL);
     Serial.print("\t");
     Serial.print(L_Y_VAL);
     Serial.print("\t");
     Serial.print(R_X_VAL);
     Serial.print("\t");
     Serial.print(R_Y_VAL);
     Serial.print("\t");
     Serial.print(L_POT_VAL);
     Serial.print("\t");
     Serial.print(R_POT_VAL);
     Serial.print("\t");
     Serial.print(L_PIN_STATE);
     Serial.print("\t");
     Serial.print(R_PIN_STATE);
     Serial.print("\t");
     Serial.print(L_Trig_STATE);
     Serial.print("\t");
     Serial.print(R_Trig_STATE);
     Serial.println("");
     delay(10);
    }
    }
    
    else
    {
        Serial.end();
        Serial.begin(115200);
    }
}

boolean PrintState = false;
boolean readstate = false;
String rawdata[256] = {};

//Function For Communicaton between ESP32 and ARDUINO NANO.
void SerialCommunication() {
    //wait for esp32 to initialise
    
        if (Serial.read() == 'S') {
            readstate = true;
            Serial.print("testok");
        }
    


    /*if (Serial.available() > 0) {
        int ReadBytes = Serial.read();
        if (ReadBytes == 'S') {
            PrintState = true;
        }
        
        else if (ReadBytes == 'E' && PrintState) {
            PrintState = false;
            if (!PrintState) {
                Serial.end();
                Serial.begin(115200);
            }
        }
    }
*/
    if (PrintState) {
                Serial.println(L_X_VAL);
            }
}

void setup() {
    pinMode(L_X, INPUT);
    pinMode(L_Y, INPUT);
    pinMode(L_PIN, INPUT_PULLUP);
    pinMode(R_X, INPUT);
    pinMode(R_Y, INPUT);
    pinMode(R_PIN, INPUT_PULLUP);
    pinMode(L_POT, INPUT);
    pinMode(R_POT, INPUT);
    pinMode(L_Trig, INPUT_PULLUP);
    pinMode(R_Trig, INPUT_PULLUP);

    Serial.begin(115200);
}

void loop() {
    ReadSense();
    //PrintFunc();
    SerialCommunication();
}