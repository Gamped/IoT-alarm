/*
    Header file for keeping readings from sensors
*/

#ifndef Readings_h
#define Readings_h

#include "Arduino.h"
#include "ReadingElement.h"


// Class for interacting with, and storing, the readings
class Readings{
    public:
        Readings();
        ReadingElement<int> readingsLDR;
        ReadingElement<unsigned long> readingsUltrasonic;
};

#endif
