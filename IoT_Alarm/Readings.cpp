/*
    Code file for keeping readings from sensors
*/
#include "Arduino.h"
#include "Readings.h"

// Constructors
Readings::Readings(){ }

// Get the ultrasonic readings array
unsigned long* Readings::GetUltrasonicReadings(){
    return Readings::readingsUltrasonic;
}

// Get the LDR readings array
int* Readings::GetLDRReadings(){ return Readings::readingsLDR; }

// Add a reading to a reading array
template <class T>
void Readings::AddReading(T reading, 
                          T toReadingsList[], 
                          int* nextIndex){
    toReadingsList[*nextIndex] = reading;

    if (*nextIndex  >= ((int)READING_LIST_SIZE - 1)){
        *nextIndex = 0;
    } else (*nextIndex)++;                   
}

// Return the last 
int Readings::GetLastLDR(){
    if (Readings::nextLDRIndex == 0){
        return Readings::readingsLDR[(int)READING_LIST_SIZE - 1];
    } else return Readings::readingsLDR[Readings::nextLDRIndex -1];
} 

// Get the last reading added to readingArray
template <class T>
T GetLastAdded(T fromArray[], int nextIndex){
    if (nextIndex == 0){
        return fromArray[(int)READING_LIST_SIZE - 1];
    } else return fromArray[nextIndex - 1];
}

// Calculate and return the mean of a readings array 
template <class T>
double Readings::GetMean(T readingsList[]){
    double sum = 0.0;

    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        sum += (double)readingsList[i];
    }
    
    return sum / (double)READING_LIST_SIZE;
}

// Calculate and return the standard deviation of a readings array
template <class T>
double GetStdDeviation(T readingsList[], double mean);
    double sum = 0.0;

    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        sum +=  pow(((double)readingsList[i] - mean), 2);
    }
    
    return sqrt(sum / (double)READING_LIST_SIZE);
}