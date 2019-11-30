/*
    Header file for time-related functionality
*/

#ifndef AlarmTime_h
#define AlarmTime_h

#include "Arduino.h"

class AlarmTime{
    public:
        AlarmTime();
        short GetSystemTimeTwoSecFormat();
        void PrintTimeTwoSecFormat(short t);
};

#endif