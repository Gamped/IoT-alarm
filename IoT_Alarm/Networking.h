/*
    Header file for controlling the networking (simulation)
*/

#ifndef Networking_h
#define Networking_h

#include "Arduino.h"

// Container class for an alarm message
class AlarmMessage {
    public:
        char type;
        short timeStamp;
        long valueLDR;
        long valueUltrasonic;
        bool valuePIR; 
};

// Queue for alarm messages
class AlarmMessageQueue {
    public:
        AlarmMessage data;
        bool containsData = false; // Since C++ object cannot be NULL
        bool hasEntryBehindInQueue = false; // Since C++ object cannot be NULL
        AlarmMessageQueue * next;
};

// Class for the networking
class Networking{
    private:
        AlarmMessageQueue messageQueue;
        unsigned long lastMessageSent;
        void SendAlarmMessage(AlarmMessage msg);
    public:
        Networking();
        void CheckAlarmMessageQueue();
        void ResetMessageDelay();
        void AddMessageToQueue(AlarmMessage msg);
        AlarmMessage MakeAlarmMessage(char type, 
                                      short timeStamp, 
                                      long valueLDR, 
                                      long valueUltrasonic, 
                                      bool valuePIR);
};

#endif
