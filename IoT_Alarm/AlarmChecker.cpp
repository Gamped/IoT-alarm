 /*
    Code file for checking if an alarm should be triggered
*/
#include "Arduino.h"
#include "AlarmChecker.h"

// Constructor
AlarmChecker::AlarmChecker(){ }

// Check if an alarm has happened
// Returns alarm type OR 'A' for no alarm
// Note: Please refer to "Type of alarm" section in report for alarm-type-table
char AlarmChecker::CheckForAlarm(Readings *r, 
                                 unsigned long readingUltra,
                                 bool readingPIR,
                                 int readingLDR){
    bool resultLDR, resultUltra;

    // See if alarm on LDR and/or ultrasonic
    resultLDR = AlarmChecker::CheckIfAlarm(&(r->readingsLDR), readingLDR, (double)LENIANCE_LDR);
    resultUltra = AlarmChecker::CheckIfAlarm(&(r->readingsUltrasonic), readingUltra, (double)LENIANCE_ULTRA);

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
