/*
    Header file for checking if an alarm should be triggered
*/

#ifndef AlarmChecker_h
#define AlarmChecker_h

#include "Arduino.h"
#include "Readings.h"

#define LENIANCE_ULTRA 10
#define LENIANCE_LDR 30

class AlarmChecker{
    private:
        bool CheckUltrasonic(Readings *r, unsigned long reading);
        bool CheckLDR(Readings *r, int reading);
    public:
        AlarmChecker();
        char CheckForAlarm(Readings *r, 
                           unsigned long readingUltra,
                           bool readingPIR,
                           int readingLDR);
};

#endif
