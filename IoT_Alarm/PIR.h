/*
    Header file for controlling the PIR sensor
*/

#ifndef PIR_h
#define PIR_h

#include "Arduino.h"

class PIR{
    private:
        int pirPin;
    public:
        PIR(int pin);
        bool Read();
};

#endif