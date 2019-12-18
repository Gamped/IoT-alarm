/*
    Code file for controlling the networking (simulation)
*/
#include "Arduino.h"
#include "Networking.h"

// Constructor
Networking::Networking(){ Networking::lastMessageSent = 0; }

// Send alarm message
void Networking::SendAlarmMessage(AlarmMessage msg){
    Serial.println("=== !ALARM! ===");
    Serial.println(msg.type);
    Serial.println(msg.timeStamp);
    Serial.println(msg.valueLDR);
    Serial.println(msg.valueUltrasonic);
    Serial.println(msg.valuePIR);
    Serial.println("=== !ALARM! ===");
}

// Check the queue if a message should be sent, and if alllowed to send
void Networking::CheckAlarmMessageQueue(){
    if (Networking::messageQueue.containsData) {
        // Verify time between messages are meeting required wait-time
        if (Networking::lastMessageSent == 0 || millis() - Networking::lastMessageSent >= MS_BETWEEN_MSG){
            Networking::SendAlarmMessage(Networking::messageQueue.data);
            Networking::RemoveFirstIndex();

            // Set time for last message sent and reduce amount stored
            Networking::lastMessageSent = millis();
        }
    }
}

// Resets the time since last message counter
void Networking::ResetMessageDelay(){ Networking::lastMessageSent = 0; }

// Adds a message to the message queue
void Networking::AddMessageToQueue(AlarmMessage msg){                            
    // Verfiy it will not go over max limit
    if (Networking::msgAmount < (int)MAX_MSG){
        Networking::PrivateAddToQueue(msg);
    } else { // ...remove oldest message and add this
        Networking::RemoveFirstIndex();
        Networking::PrivateAddToQueue(msg);
    }
}

// Remove the first index of the queue
void Networking::RemoveFirstIndex(){
    // Remove first index (and replace)
    if (Networking::messageQueue.hasEntryBehindInQueue){
        Networking::messageQueue = *Networking::messageQueue.next;
    } else {
        // Just allow overwrite of its data, as it is the first element
        Networking::messageQueue.containsData = false;
    }
    Networking::msgAmount--;
}

// Function used to add to queue, but private as checks needs to be done in public
void Networking::PrivateAddToQueue(AlarmMessage msg){
    if (!Networking::messageQueue.containsData){
        Networking::messageQueue.data = msg;
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
        current->hasEntryBehindInQueue = true; 
    }
    Networking::msgAmount++;
}

// Make new alarm message
AlarmMessage Networking::MakeAlarmMessage(char type, 
                                          short timeStamp, 
                                          long valueLDR, 
                                          long valueUltrasonic, 
                                          bool valuePIR){
    AlarmMessage msg;
    
    msg.type = type;
    msg.timeStamp = timeStamp;
    msg.valueLDR = valueLDR;
    msg.valueUltrasonic = valueUltrasonic;
    msg.valuePIR = valuePIR;

    return msg;
}
