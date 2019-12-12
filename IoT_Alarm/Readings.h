/*
    Header file for keeping readings from sensors
*/

#ifndef Readings_h
#define Readings_h

#include "Arduino.h"

#define READING_LIST_SIZE 3

// Class for interacting with, and storing, the readings
class Readings{
    private:
        bool lastPIRReading;
        unsigned long readingsUltrasonic[READING_LIST_SIZE];
        int readingsLDR[READING_LIST_SIZE];
        int nextUltrasonicIndex = 0, nextLDRIndex = 0;
    public:
        Readings();
        void ReadingPIR(bool reading);
        void ReadingUltrasonic(unsigned long reading);
        void ReadingLDR(int reading);
        double GetUltrasonicMean();
        double GetLDRMean();
        double GetUltrasonicVariance();
        double GetLDRVariance();        
        bool GetPIRReading();
};

#endif