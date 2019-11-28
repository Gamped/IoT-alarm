/*
    Code file for controlling the PIR sensor
*/
#include "Arduino.h"
#include "Ultrasonic.h"

// Constructor
Ultrasonic::Ultrasonic(int echoPin, int trigPin){
    ultrasonicEchoPin = echoPin;
    ultrasonicTrigPin = trigPin;
    pinMode(ultrasonicEchoPin, INPUT);
    pinMode(ultrasonicTrigPin, OUTPUT);
}

// Private function to convert microseconds into centimeters
unsigned long Ultrasonic::ConvertToCM(unsigned long microseconds){
    return microseconds / (unsigned long)29 / (unsigned long)2;
}

// Function to get the microseconds it takes to send/recieve sonar
unsigned long Ultrasonic::ReadMicroseconds(){
    // Ping sensor to send out sonar
    digitalWrite(ultrasonicTrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonicTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonicTrigPin, LOW);

    // Return the time it took to get sound back
    return pulseIn(ultrasonicEchoPin, HIGH);
}

// Function which triggers the reading and returns distance in centimeter
unsigned long Ultrasonic::ReadCM(){
    return Ultrasonic::ConvertToCM(Ultrasonic::ReadMicroseconds());
}