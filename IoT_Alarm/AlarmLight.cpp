/*
    Code file for controlling the alarm light(s)
*/
#include "Arduino.h"
#include "AlarmLight.h"

// Constructor
AlarmLight::AlarmLight(int pin){
    alarmLightPin = pin;
    pinMode(alarmLightPin, OUTPUT);
}

// Sets the light to the desired state
// NOTE: HIGH and LOW are defined as true/false
void AlarmLight::SetLight(bool state){
    digitalWrite(alarmLightPin, state);
}