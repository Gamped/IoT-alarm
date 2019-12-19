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
bool PIR::Read(){ 
    bool result = false;
    
    if (PIR::lastReadingTime == 0 || (millis() - PIR::lastReadingTime) >= (unsigned long)PIR_READING_DELAY_MS){
        result = digitalRead(PIR::pirPin);

        // Set time since last positive reading if found
        if (result) { PIR::lastReadingTime = millis(); }

        return result;
    } else return false; 
}
