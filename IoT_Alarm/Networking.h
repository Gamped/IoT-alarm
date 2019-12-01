/*
    Header file for controlling the networking (simulation)
*/

#ifndef Networking_h
#define Networking_h

#include "Arduino.h"

// Custom structure for an alarm message
typedef struct alarmMessage {
  char type;
  short timeStamp;
  long valueLDR;
  long valueUltrasonic;
  char bitmap; 
} alarmMessage_t;

// Queue for alarm messages
typedef struct alarmMessageQueue {
  alarmMessage_t data;
  struct alarmMessageQueue *next;
} alarmMessageQueue_t;

class Networking{
    private:
        alarmMessageQueue_t *messageQueue;
        unsigned long lastMessageSent;
        void SendAlarmMessage(alarmMessage_t message);
    public:
        Networking();
        void CheckAlarmMessageQueue();
        void ResetMessageDelay();
        void AddMessageToQueue(alarmMessage_t msg);
        alarmMessage_t MakeAlarmMessage(char type, 
                                        short timeStamp, 
                                        long valueLDR, 
                                        long valueUltrasonic, 
                                        char bitmap);
};

#endif