/*
    Code file for controlling the LDR sensor
*/
#include "Arduino.h"
#include "LDR.h"

// Constructor
LDR::LDR(int pin){
    ldrPin = pin;
    pinMode(ldrPin, INPUT);
}

// Reads the PIR and returns if it's been triggered
int LDR::Read(){
    int result = analogRead(ldrPin);
    return result;
}