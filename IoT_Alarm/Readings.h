/*
    Header file for keeping readings from sensors
*/

#ifndef Readings_h
#define Readings_h

#include "Arduino.h"

#define READING_LIST_SIZE 5

// Class for interacting with, and storing, the readings
class Readings{
    private:
        unsigned long readingsUltrasonic[READING_LIST_SIZE];
        int readingsLDR[READING_LIST_SIZE];
        int nextUltrasonicIndex = 0, nextLDRIndex = 0;
    public:
        Readings();
        void AddReadingUltrasonic(unsigned long reading);
        void AddReadingLDR(int reading);
        double GetUltrasonicMean();
        double GetLDRMean();
        double GetUltrasonicVariance();
        double GetLDRVariance();
        unsigned long GetLastUltrasonic();
        int GetLastLDR();        
};

#endif
