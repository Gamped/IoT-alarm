/*
    Header file for keeping readings from sensors
*/

#ifndef Readings_h
#define Readings_h

#include "Arduino.h"

#define READING_LIST_SIZE 15

// A "linked list" class for keeping readings
class ReadingElemet{
    public:
        bool containsData = false; // Since C++ object cannot be NULL
        bool hasEntryBehindInList = false; // Since C++ object cannot be NULL
        ReadingElemet * next;
};

// Child classes for the data types, as no support for "auto" in classes :(
class ReadingElementBool : public ReadingElemet {
    public:
        bool data;
};
class ReadingElementUnsignedLong : public ReadingElemet {
    public:
        unsigned long data;
};
class ReadingElementInt : public ReadingElemet {
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
        void UpdateList(ReadingElemet * list, 
                        ReadingElemet * toBeAdded);
    public:
        Readings();
        void AddPIRReading(bool reading);
        void AddUltrasonicReading(unsigned long reading);
        void AddLDRReading(int reading);
        ReadingElemet GetReadingsPIR();
        ReadingElemet GetReadingsUltrasonic();
        ReadingElemet GetReadingsLDR();
};

#endif