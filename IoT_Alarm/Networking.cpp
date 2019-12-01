/*
    Code file for controlling the networking (simulation)
*/
#include "Arduino.h"
#include "Networking.h"

#define NETWORK_DELAY_MS 100
#define MS_BETWEEN_MSG 600000

// Constructor
Networking::Networking(){
    Networking::mesageQueue = NULL;
    Networking::lastMessageSent = 0;
}

// Send alarm message ... with simulated delay
void Networking::SendAlarmMessage(alarmMessage_t message){
    delay(NETWORK_DELAY_MS);
    Serial.println("=== !ALARM! ===")
    Serial.println(message->type);
    Serial.println(message->timeStamp);
    Serial.println(message->valueLDR);
    Serial.println(message->valueUltrasonic);
    Serial.println(message->bitmap);
    Serial.println("=== !ALARM! ===");
}

// Check the queue if a message should be sent, and if alllowed to send
void Networking::CheckAlarmMessageQueue(){
    if (mesageQueue != NULL) {
        // Verify time between messages are meeting required wait-time
        if (Networking::lastMessageSent == 0 || millis() - Networking::lastMessageSent >= MS_BETWEEN_MSG){
            // Send message
            Networking::SendAlarmMessage(Networking::mesageQueue->data);

            // Remove first index (and replace)
            if (Networking::mesageQueue->next == NULL){
                Networking::mesageQueue = NULL;
            } else {
                alarmMessageQueue_t *temp = Networking::mesageQueue->next;
                free(Networking::mesageQueue);
                Networking::mesageQueue = temp;
            }
        }
    }
}

// Resets the time since last message counter
void Networking::ResetMessageDelay(){
    Networking::lastMessageSent = millis();
}

// Adds a message to the message queue
void Networking::AddMessageToQueue(alarmMessage_t msg){
    if (Networking::messageQueue == NULL){
        Networking::messageQueue = malloc(sizeof(alarmMessageQueue_t));
        Networking::mesageQueue->data = msg;
    } else {
        alarmMessageQueue_t *newIndex = malloc(sizeof(alarmMessageQueue_t));
        alarmMessageQueue_t current = Networking::mesageQueue;
        
        // Scroll through queue to find end
        while (current->next != NULL){
            current = current->next;
        }
        
        // Write data to newIndex and add it to queue
        newIndex->data = msg;
        current->next = newIndex;
    }
}

// Construct an alarmMessage
alarmMessage_t Networking::MakeAlarmMessage(char type, 
                                            short timeStamp, 
                                            long valueLDR, 
                                            long valueUltrasonic, 
                                            char bitmap){
    alarmMessage_t *newMessage = malloc(sizeof(alarmMessage_t));
    
    newMessage->type = type;
    newMessage->timeStamp = timeStamp;
    newMessage->valueLDR = valueLDR;
    newMessage->valueUltrasonic = valueUltrasonic;
    newMessage->bitmap = bitmap;
    
    return newMessage;
}