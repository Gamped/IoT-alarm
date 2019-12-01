/*
    Code file for controlling the PIR sensor
*/
#include "Arduino.h"
#include "Ultrasonic.h"

// Constructor
Ultrasonic::Ultrasonic(int echoPin, int trigPin){
    Ultrasonic::ultrasonicEchoPin = echoPin;
    Ultrasonic::ultrasonicTrigPin = trigPin;
    pinMode(Ultrasonic::ultrasonicEchoPin, INPUT);
    pinMode(Ultrasonic::ultrasonicTrigPin, OUTPUT);
}

// Private function to convert microseconds into centimeters
unsigned long Ultrasonic::ConvertToCM(unsigned long microseconds){
    return microseconds / (unsigned long)29 / (unsigned long)2;
}

// Function to get the microseconds it takes to send/recieve sonar
unsigned long Ultrasonic::ReadMicroseconds(){
    // Ping sensor to send out sonar
    digitalWrite(Ultrasonic::ultrasonicTrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(Ultrasonic::ultrasonicTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Ultrasonic::ultrasonicTrigPin, LOW);

    // Return the time it took to get sound back
    return pulseIn(Ultrasonic::ultrasonicEchoPin, HIGH);
}

// Function which triggers the reading and returns distance in centimeter
unsigned long Ultrasonic::ReadCM(){
    return Ultrasonic::ConvertToCM(Ultrasonic::ReadMicroseconds());
}