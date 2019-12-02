/*
    Code file for time-related functionality
*/
#include "Arduino.h"
#include "AlarmTime.h"

#define DAY_TWO_SEC_COUNT 43200
#define MINUTE_TWO_SEC 30
#define HOUR_TWO_SEC 1800
#define MILLIS_TO_TWO_SEC 2000

// Constructor
AlarmTime::AlarmTime(){ }

// Returns the time with 2 second as the smallest unit
short AlarmTime::GetSystemTimeTwoSecFormat(){
    unsigned long currTime = millis();
    currTime /= MILLIS_TO_TWO_SEC; 

    // Ensure not going over 2 bytes
    currTime %= DAY_TWO_SEC_COUNT;

    return (short)currTime;
}

// Prints time based upon a short in 2-sec-format
void AlarmTime::PrintTimeTwoSecFormat(short t){
    Serial.print("Hour: ");
    Serial.println(t / HOUR_TWO_SEC);
    t %= HOUR_TWO_SEC;
    Serial.print("Min: ");
    Serial.println(t / MINUTE_TWO_SEC);
    t %= MINUTE_TWO_SEC;
    Serial.print("Sec: ");
    Serial.println(t * 2);
}
