/*
    Header file for keeping readings from sensors
*/

#ifndef Readings_h
#define Readings_h

#include "Arduino.h"

#define READING_LIST_SIZE 15

// A "linked list" class for keeping readings
class ReadingElement{
    public:
        bool containsData = false; // Since C++ object cannot be NULL
        bool hasEntryAfterInList = false; // Since C++ object cannot be NULL
        ReadingElement * next;
};

// Child classes for the data types, as no support for "auto" in classes :(
class ReadingElementBool : public ReadingElement {
    public:
        bool data;
};
class ReadingElementUnsignedLong : public ReadingElement {
    public:
        unsigned long data;
};
class ReadingElementInt : public ReadingElement {
    public:
        int data;
};

// Class for interacting with the readings
class Readings{
    private:
        bool lastPIRReading;
        ReadingElementBool readingsPIR;
        ReadingElementUnsignedLong readingsUltrasonic;
        ReadingElementInt readingsLDR;
        void UpdateList(ReadingElement * list, 
                        ReadingElement * toBeAdded);
    public:
        Readings();
        void AddPIRReading(bool reading);
        void AddUltrasonicReading(unsigned long reading);
        void AddLDRReading(int reading);
        ReadingElementBool GetReadingsPIR();
        ReadingElementUnsignedLong GetReadingsUltrasonic();
        ReadingElementInt GetReadingsLDR();
};

#endif