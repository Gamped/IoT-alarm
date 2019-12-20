 /*
    Code file for checking if an alarm should be triggered
*/
#include "Arduino.h"
#include "AlarmChecker.h"

// Constructor
AlarmChecker::AlarmChecker(){ }

// Check if an alarm has happened
// Returns alarm type OR 'A' for no alarm
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
        return 'A'; // No alarm
    } else if (!resultLDR && !resultUltra && readingPIR){
        return '0'; // PIR triggered
    } else if (resultLDR && !resultUltra && readingPIR){
        return '1'; // PIR and LDR triggered
    } else if (!resultLDR && resultUltra && readingPIR){
        return '2'; // PIR and Ultrasonic triggered
    } else if (resultLDR && resultUltra && readingPIR){
        return '3'; // PIR, LDR and Ultrasonic triggered
    } else if (resultLDR && resultUltra && !readingPIR){
        return '4'; // LDR and Ultrasonic triggered
    } else if (resultLDR && !resultUltra && !readingPIR){
        return '5'; // LDR triggered
    } else if (!resultLDR && resultUltra && !readingPIR){
        return '6'; // Ultrasonic triggered
    } else return 'A';
}
