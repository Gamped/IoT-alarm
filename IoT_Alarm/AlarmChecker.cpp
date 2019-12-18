 /*
    Code file for checking if an alarm should be triggered
*/
#include "Arduino.h"
#include "AlarmChecker.h"

// Constructor
AlarmChecker::AlarmChecker(){ }

// Check if there should be alarm and add to readings
bool AlarmChecker::CheckUltrasonic(Readings *r, unsigned long reading){
    // If there is a reading
    if (reading != 0){
        // See if an alarm should be triggerd
        if (reading < (r->GetUltrasonicMean() - ((r->GetUltrasonicStdDeviation() / 2) + (int)LENIANCE_ULTRA))
            || reading > (r->GetUltrasonicMean() + ((r->GetUltrasonicStdDeviation() / 2) + (int)LENIANCE_ULTRA))){
            r->AddReadingUltrasonic(reading);
            // Trigger alarm, as it is not a "normal" reading
            return true;
        }
    }
    r->AddReadingUltrasonic(reading);
    return false;
}

// Check if there should be alarm and add to readings
bool AlarmChecker::CheckLDR(Readings *r, int reading){
    // If there is a reading
    if (reading != 0){
        // See if an alarm should be triggerd
        if (reading < (r->GetLDRMean() - ((r->GetLDRStdDeviation() / 2) + (int)LENIANCE_LDR))
            || reading > (r->GetLDRMean() + ((r->GetLDRStdDeviation() / 2) + (int)LENIANCE_LDR))){
            r->AddReadingLDR(reading);
            // Trigger alarm, as it is not a "normal" reading            
            return true;
        }
    }
    r->AddReadingLDR(reading);
    return false;
}

// Check if an alarm has happened
// Returns alarm type OR 'A' for no alarm
// Note: Please refer to "Type of alarm" section in report for alarm-type-table
char AlarmChecker::CheckForAlarm(Readings *r, 
                                 unsigned long readingUltra,
                                 bool readingPIR,
                                 int readingLDR){
    bool resultLDR = AlarmChecker::CheckLDR(r, readingLDR);
    bool resultUltra = AlarmChecker::CheckUltrasonic(r, readingUltra);

    // Figure out if there is an alarm
    if (!resultLDR && !readingUltra && !readingPIR){
        return 'A';
    } else if (!resultLDR && !resultUltra && readingPIR){
        return '0';
    } else if (!resultLDR && !resultUltra && readingPIR){
        return '1';
    } else if (!resultLDR && resultUltra && readingPIR){
        return '2';
    } else if (resultLDR && resultUltra && readingPIR){
        return '3';
    } else if (resultLDR && resultUltra && !readingPIR){
        return '4';
    } else if (resultLDR && !resultUltra && !readingPIR){
        return '5';
    } else if (!resultLDR && resultUltra && !readingPIR){
        return '6';
    } else return 'A';
}
