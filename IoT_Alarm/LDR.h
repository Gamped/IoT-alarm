/*
    Header file for controlling the LDR sensor
*/

#ifndef LDR_h
#define LDR_h

#include "Arduino.h"

class LDR{
    private:
        int ldrPin;
    public:
        LDR(int pin);
        int Read();
};

#endif