/*
    Header file for controlling the networking (simulation)
*/

#ifndef Networking_h
#define Networking_h

#include "Arduino.h"

// Maximum store 4 hours worth of messages (on sigfox network) to not overflow (total 288 byte)
#define MAX_MSG 24
// By default wait 10 min between sending msg, to live up to sigfox limit
#define MS_BETWEEN_MSG 600000

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
        int msgAmount = 0;
        void PrivateAddToQueue(AlarmMessage msg);
        void RemoveFirstIndex();
    public:
        Networking();
        void CheckAlarmMessageQueue();
        void ResetMessageDelay();
        void AddMessageToQueue(AlarmMessage msg);
        void RemoveAllFromQueue();
        AlarmMessage MakeAlarmMessage(char type, 
                                      short timeStamp, 
                                      long valueLDR, 
                                      long valueUltrasonic, 
                                      bool valuePIR);
};

#endif
