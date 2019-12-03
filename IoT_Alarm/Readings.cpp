/*
    Code file for keeping readings from sensors
*/
#include "Arduino.h"
#include "Readings.h"

// Constructor
Readings::Readings(){}

// Function to update a list, removing the last index if above limit
void Readings::UpdateList(ReadingElemet * list, ReadingElemet * toBeAdded){
    // If first reading ever
    if (!list->containsData && !list->hasEntryBehindInList){
        /* code */
    } else {
        /* code */
    }
}

// Makes and adds PIR readings
void Readings::AddPIRReading(bool reading){
    ReadingElementBool newElement;
    newElement.data = reading;
    newElement.containsData = true;
    Readings::UpdateList(&(Readings::readingsPIR), &newElement);
}

// Makes and adds Ultrasonic readings
void Readings::AddUltrasonicReading(unsigned long reading){
    ReadingElementUnsignedLong newElement;
    newElement.data = reading;
    newElement.containsData = true;
    Readings::UpdateList(&(Readings::readingsUltrasonic), &newElement);
}

// Makes and adds LDR readings
void Readings::AddLDRReading(int reading){
    ReadingElementInt newElement;
    newElement.data = reading;
    newElement.containsData = true;
    Readings::UpdateList(&(Readings::readingsLDR), &newElement);
}

// Getters
ReadingElemet Readings::GetReadingsPIR(){ return readingsPIR; }
ReadingElemet Readings::GetReadingsUltrasonic(){ return readingsUltrasonic; }
ReadingElemet Readings::GetReadingsLDR(){ return readingsLDR; }