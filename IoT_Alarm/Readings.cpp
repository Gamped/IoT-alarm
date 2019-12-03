/*
    Code file for keeping readings from sensors
*/
#include "Arduino.h"
#include "Readings.h"

// Constructor
Readings::Readings(){}

// Function to update a list, removing the last index if above limit
void Readings::UpdateList(ReadingElement * list, ReadingElement * toBeAdded){
    // If first reading ever
    if (!list->containsData && !list->hasEntryAfterInList){
        list = toBeAdded;
    } else {
        ReadingElement temp = *list;

        // Add toBeAdded as first element
        toBeAdded->next = &temp;
        toBeAdded->hasEntryAfterInList = true;
        list = toBeAdded;

        // Scroll through to see if list is too long
        ReadingElement * current = list;
        for (int i; i < (int)READING_LIST_SIZE; i++){
            if (current->hasEntryAfterInList){
                current = current->next;
            } else return; // As no need to do more, due to list being shorter
        }
        
        // If it got this far, then remove last element
        delete current->next;
        current->hasEntryAfterInList = false;
    }
}

// Makes and adds PIR readings
void Readings::AddPIRReading(bool reading){
    ReadingElementBool * newElement;
    newElement->data = reading;
    newElement->containsData = true;
    Readings::UpdateList(&(Readings::readingsPIR), newElement);
}

// Makes and adds Ultrasonic readings
void Readings::AddUltrasonicReading(unsigned long reading){
    ReadingElementUnsignedLong * newElement;
    newElement->data = reading;
    newElement->containsData = true;
    Readings::UpdateList(&(Readings::readingsUltrasonic), newElement);
}

// Makes and adds LDR readings
void Readings::AddLDRReading(int reading){
    ReadingElementInt * newElement;
    newElement->data = reading;
    newElement->containsData = true;
    Readings::UpdateList(&(Readings::readingsLDR), newElement);
}

// Getters
ReadingElementBool Readings::GetReadingsPIR(){ 
    return Readings::readingsPIR; 
}
ReadingElementUnsignedLong Readings::GetReadingsUltrasonic(){ 
    return Readings::readingsUltrasonic; 
}
ReadingElementInt Readings::GetReadingsLDR(){ 
    return Readings::readingsLDR; 
}