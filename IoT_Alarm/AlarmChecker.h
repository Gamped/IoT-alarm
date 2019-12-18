/*
    Header file for checking if an alarm should be triggered
*/

#ifndef AlarmChecker_h
#define AlarmChecker_h

#include "Arduino.h"
#include "Readings.h"
#include "ReadingElement.h"

#define LENIANCE_ULTRA 10
#define LENIANCE_LDR 35

class AlarmChecker{
    private:
        template <class T>
        bool CheckIfAlarm(ReadingElement<T> *r, T reading, double leniance);
    public:
        AlarmChecker();
        char CheckForAlarm(Readings *r, 
                           unsigned long readingUltra,
                           bool readingPIR,
                           int readingLDR);
};

/*
    To avoid C++ compiler scope problems with templates
    template functionality of the class is in this .h file :)
*/

// Check if there should be alarm and add to readings
template <class T>
bool AlarmChecker::CheckIfAlarm(ReadingElement<T> *r, T reading, double leniance){
    // If there are a reading
    if (reading != 0){
        bool less, more;
        double mean, sigmaAndLeniance;
        
        // Calculate only once
        sigmaAndLeniance = (r->GetStdDeviation()* 3) + leniance;
        mean = r->GetMean();

        // Check if more or less
        less = reading < (mean - sigmaAndLeniance);
        more = reading > (mean + sigmaAndLeniance);
        
        // See if an alarm should be triggerd
        if (more || less){
            r->AddReading(reading);
            // Trigger alarm, as it is not a "normal" reading
            return true;
        }

        // No alarm, so just add reading
        r->AddReading(reading);
    }
    return false;
}

#endif
