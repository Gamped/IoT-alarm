/*
    Code file for checking if an alarm should be triggered
*/
#include "Arduino.h"
#include "AlarmChecker.h"

#define EULERS_NUMBER 2.718281828459045
#define PI_ALARM_CHECK 3.141592653589793

// Constructor
AlarmChecker::AlarmChecker(){ }

// Calculate the chance of a reading happening using normal distribution
double AlarmChecker::CalculateChance(double result, 
                                     double my, 
                                     double sigma){
    double base = 0.0, exponent = 0.0; // of last pow() in equation

    // Calculate base
    base = (2 * (double)PI_ALARM_CHECK) * pow(sigma, 2);
    base = sqrt(base);
    base = (double)1 / base;
    base *= (double)EULERS_NUMBER;

    // Calculate exponent
    exponent = (double)2 * pow(sigma, 2);
    exponent = pow((result - my), 2) / exponent;
    exponent *= (double)-1;

    // Return result
    return pow(base, exponent);
}

// Check if an alarm has happened
// Returns alarm type OR 'A' for no alarm
char AlarmChecker::CheckForAlarm(bool pir, 
                                 unsigned long ultrasonic, 
                                 int ldr){
    //
}
