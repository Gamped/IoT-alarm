/*
    Header file for controlling the alarm light(s)
*/

#ifndef AlarmLight_h
#define AlarmLight_h

#include "Arduino.h"

class AlarmLight{
    private:
        int alarmLightPin;
    public:
        AlarmLight(int pin);
        void SetLight(bool state);
};

#endif