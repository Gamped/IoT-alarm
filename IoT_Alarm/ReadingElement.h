/*
    Header file for keeping readings from a specific sensor
*/

#ifndef ReadingElement_h
#define ReadingElement_h

#include "Arduino.h"

#define READING_LIST_SIZE 8

// Class for interacting with, and storing, the readings
template <class T>
class ReadingElement{
    private:
        int nextIndex = 0;
        T readingList[READING_LIST_SIZE];
    public:
        void AddReading(T reading);
        T GetLastAdded();
        double GetMean();
        double GetStdDeviation();    
};

/*
    To avoid C++ compiler scope problems with templates
    all functionality of the class is in this .h file :)
*/

// Add a reading to a reading array
template <class T>
void ReadingElement<T>::AddReading(T reading){
    readingList[nextIndex] = reading;

    if (nextIndex  >= ((int)READING_LIST_SIZE - 1)){
        nextIndex = 0;
    } else nextIndex++;                   
}

// Get the last reading added to readingArray
template <class T>
T ReadingElement<T>::GetLastAdded(){
    if (nextIndex == 0){
        return readingList[(int)READING_LIST_SIZE - 1];
    } else return readingList[nextIndex - 1];
}

// Calculate and return the mean of a readings array 
template <class T>
double ReadingElement<T>::GetMean(){
    double sum = 0.0;

    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        sum += (double)readingList[i];
    }
    
    return sum / (double)READING_LIST_SIZE;
}

// Calculate and return the standard deviation of a readings array
template <class T>
double ReadingElement<T>::GetStdDeviation(){
    double sum = 0.0, mean = ReadingElement<T>::GetMean();

    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        sum +=  pow(((double)readingList[i] - mean), 2);
    }
    
    return sqrt(sum / (double)READING_LIST_SIZE);
}

#endif
