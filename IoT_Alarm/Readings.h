/*
    Header file for keeping readings from sensors
*/

#ifndef Readings_h
#define Readings_h

#include "Arduino.h"

#define READING_LIST_SIZE 8

// Class for interacting with, and storing, the readings
class Readings{
    private:
        unsigned long readingsUltrasonic[READING_LIST_SIZE];
        int readingsLDR[READING_LIST_SIZE];
    public:
        int nextUltrasonicIndex = 0, nextLDRIndex = 0;
        Readings();
        unsigned long* GetUltrasonicReadings();
        int* GetLDRReadings();

        template <class T>
        void AddReading(T reading, 
                        T toReadingsList[], 
                        int* nextIndex);

        template <class T>
        T GetLastAdded(T fromArray[], int nextIndex);

        template <class T>
        double GetMean(T readingsList[]);

        template <class T>
        double GetStdDeviation(T readingsList[], double mean);    
};

#endif
