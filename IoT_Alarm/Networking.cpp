/*
    Code file for controlling the networking (simulation)
*/
#include "Arduino.h"
#include "Networking.h"

#define MS_BETWEEN_MSG 600000

// Constructor
Networking::Networking(){
    Networking::lastMessageSent = 0;
}

// Send alarm message
void Networking::SendAlarmMessage(AlarmMessage msg){
    Serial.println("=== !ALARM! ===");
    Serial.println(msg.type);
    Serial.println(msg.timeStamp);
    Serial.println(msg.valueLDR);
    Serial.println(msg.valueUltrasonic);
    Serial.println(msg.bitmap);
    Serial.println("=== !ALARM! ===");
}

// Check the queue if a message should be sent, and if alllowed to send
void Networking::CheckAlarmMessageQueue(){
    if (Networking::messageQueue.containsData) {
        // Verify time between messages are meeting required wait-time
        if (Networking::lastMessageSent == 0 || millis() - Networking::lastMessageSent >= MS_BETWEEN_MSG){
            // Send message
            Networking::SendAlarmMessage(Networking::messageQueue.data);

            // Remove first index (and replace)
            if (Networking::messageQueue.hasEntryBehindInQueue){
                Networking::messageQueue = *Networking::messageQueue.next;
            } else {
                // Just allow overwrite of its data, as it is the first element
                Networking::messageQueue.containsData = false;
            }
            // Set time for last message sent
            Networking::lastMessageSent = millis();
        }
    }
}

// Resets the time since last message counter
void Networking::ResetMessageDelay(){
    Networking::lastMessageSent = millis() < MS_BETWEEN_MSG ? 0 : millis() - MS_BETWEEN_MSG;
}

// Adds a message to the message queue
void Networking::AddMessageToQueue(AlarmMessage msg, int ID){                            
    if (!Networking::messageQueue.containsData){
        Networking::messageQueue.data = msg;
        Networking::messageQueue.ID = ID;
        Networking::messageQueue.containsData = true;
    } else {
        AlarmMessageQueue *current; 
        current = &(Networking::messageQueue);
        bool keepScrolling = true;

        // Scroll through queue to find end
        while (keepScrolling){
            if (current->hasEntryBehindInQueue){
                current = current->next;
            } else keepScrolling = false;
        }
        current->next = new AlarmMessageQueue;
        current->next->data = msg;
        current->next->containsData = true;
        current->next->ID = ID;
        current->hasEntryBehindInQueue = true; 
    }
}

// Make new alarm message
AlarmMessage Networking::MakeAlarmMessage(char type, 
                                          short timeStamp, 
                                          long valueLDR, 
                                          long valueUltrasonic, 
                                          char bitmap){
    AlarmMessage msg;
    
    msg.type = type;
    msg.timeStamp = timeStamp;
    msg.valueLDR = valueLDR;
    msg.valueUltrasonic = valueUltrasonic;
    msg.bitmap = bitmap;

    return msg;
}