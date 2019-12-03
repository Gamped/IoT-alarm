/*
    Header file for checking if an alarm should be triggered
*/

#ifndef AlarmChecker_h
#define AlarmChecker_h

#include "Arduino.h"

class AlarmChecker{
    private:
        double CalculateChance(double result, 
                               double my, 
                               double sigma);
        double CalculateMean();
        double CalculateVariance();
    public:
        AlarmChecker();
        char CheckForAlarm(bool pir, 
                           unsigned long ultrasonic, 
                           int ldr);
};

#endif
