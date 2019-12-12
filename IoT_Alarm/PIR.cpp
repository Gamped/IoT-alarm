/*
    Code file for controlling the PIR sensor
*/
#include "Arduino.h"
#include "PIR.h"

// Constructor
PIR::PIR(int pin){
    PIR::pirPin = pin;
    pinMode(PIR::pirPin, INPUT);
}

// Reads the PIR and returns if it's been triggered
bool PIR::Read(){ return digitalRead(PIR::pirPin); }