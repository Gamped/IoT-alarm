/*
    Code file for keeping readings from sensors
*/
#include "Arduino.h"
#include "Readings.h"

// Constructors
Readings::Readings(){}

// Set the last PIR reading to reading
void Readings::ReadingPIR(bool reading){
    Readings::lastPIRReading = reading;
}

// Save the last ultrasonic reading, and move pointer to next array index
void Readings::ReadingUltrasonic(unsigned long reading){
    Readings::readingsUltrasonic[Readings::nextUltrasonicIndex] = reading;
    
    if (Readings::nextUltrasonicIndex >= ((int)READING_LIST_SIZE - 1)){
        Readings::nextUltrasonicIndex = 0;
    } else Readings::nextUltrasonicIndex++;
}

// Save the last LDR reading, and move pointer to next array index
void Readings::ReadingLDR(int reading){
    Readings::readingsLDR[Readings::nextLDRIndex] = reading;
    
    if (Readings::nextLDRIndex >= ((int)READING_LIST_SIZE - 1)){
        Readings::nextLDRIndex = 0;
    } else Readings::nextLDRIndex++;
}