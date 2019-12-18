/*
    Code file for keeping readings from sensors
*/
#include "Arduino.h"
#include "Readings.h"

// Constructors
Readings::Readings(){ }

// Save the last ultrasonic reading, and move pointer to next array index
void Readings::AddReadingUltrasonic(unsigned long reading){
    Readings::readingsUltrasonic[Readings::nextUltrasonicIndex] = reading;
    
    if (Readings::nextUltrasonicIndex >= ((int)READING_LIST_SIZE - 1)){
        Readings::nextUltrasonicIndex = 0;
    } else Readings::nextUltrasonicIndex++;
}

// Save the last LDR reading, and move pointer to next array index
void Readings::AddReadingLDR(int reading){
    Readings::readingsLDR[Readings::nextLDRIndex] = reading;
    
    if (Readings::nextLDRIndex >= ((int)READING_LIST_SIZE - 1)){
        Readings::nextLDRIndex = 0;
    } else Readings::nextLDRIndex++;
}

// Calculate and return the mean of ultrasonic readings
double Readings::GetUltrasonicMean(){
    double sum = 0.0;

    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        sum += (double)Readings::readingsUltrasonic[i];
    }
    
    return sum / (double)READING_LIST_SIZE;;
}

// Calculate and return the mean of LDR readings
double Readings::GetLDRMean(){
    double sum = 0.0;

    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        sum += (double)Readings::readingsLDR[i];
    }
    
    return sqrt(sum / (double)READING_LIST_SIZE);
}

// Calculate and return the variance of ultrasonic readings
double Readings::GetUltrasonicStdDeviation(){
    double sum = 0.0, mean = Readings::GetUltrasonicMean();

    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        sum +=  pow(((double)Readings::readingsUltrasonic[i] - mean), 2);
    }
    
    return sqrt(sum / (double)READING_LIST_SIZE);
}

// Calculate and return the variance of LDR readings
double Readings::GetLDRStdDeviation(){
    double sum = 0.0, mean = Readings::GetLDRMean();

    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        sum +=  pow(((double)Readings::readingsLDR[i] - mean), 2);
    }
    
    return sum / (double)READING_LIST_SIZE;
}

// Return the last reading from Ultrasonic
unsigned long Readings::GetLastUltrasonic(){
    if (Readings::nextUltrasonicIndex == 0){
        return Readings::readingsUltrasonic[(int)READING_LIST_SIZE - 1];
    } else return Readings::readingsUltrasonic[Readings::nextUltrasonicIndex -1];
}

// Return the last 
int Readings::GetLastLDR(){
    if (Readings::nextLDRIndex == 0){
        return Readings::readingsLDR[(int)READING_LIST_SIZE - 1];
    } else return Readings::readingsLDR[Readings::nextLDRIndex -1];
}   
