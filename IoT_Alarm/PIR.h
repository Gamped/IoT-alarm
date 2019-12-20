/*
    Header file for controlling the PIR sensor
*/

#ifndef PIR_h
#define PIR_h

#include "Arduino.h"

// Due to the hardware not being able to read 6 sec after detection
#define PIR_READING_DELAY_MS 6250

class PIR{
    private:
        int pirPin;
        unsigned long lastReadingTime;
    public:
        PIR(int pin);
        bool Read();
};

#endif
