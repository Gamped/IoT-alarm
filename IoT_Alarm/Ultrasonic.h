/*
    Header file for controlling the Ultrasonic sensor
*/

#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"

class Ultrasonic{
    private:
        int ultrasonicEchoPin, ultrasonicTrigPin;
        unsigned long ConvertToCM(unsigned long microseconds);
    public:
        Ultrasonic(int echoPin, int trigPin);
        unsigned long ReadMicroseconds();
        unsigned long ReadCM();
};

#endif