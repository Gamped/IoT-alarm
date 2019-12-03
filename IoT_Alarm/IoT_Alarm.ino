/* ======== Includes ======== */
#include "PIR.h"
#include "LDR.h"
#include "Ultrasonic.h"
#include "AlarmLight.h"
#include <SPI.h>
//#include <MFRC522.h>
#include "AlarmTime.h"
#include "Networking.h"
#include "AlarmChecker.h"
#include "Readings.h"

/* ======== Define pins ======== */
#define ULTRASONIC_ECHO 2
#define ULTRASONIC_TRIG 3
#define PIR_SIG 4
#define LED_RED 5
#define RFID_RST 6
#define RFID_SDA 10
#define RFID_MOSI 11
#define RFID_MISO 12
#define LDR_SIG A3
#define RTC_SDA A4
#define RTC_SCL A5

/* ======== Global variables ======== */
PIR pir(PIR_SIG);
LDR ldr(LDR_SIG);
Ultrasonic ultrasonic(ULTRASONIC_ECHO, ULTRASONIC_TRIG);
AlarmLight alarmLight(LED_RED);
//MFRC522 mfrc522(RFID_SDA, RFID_RST);
byte readCard[4];
AlarmTime time;
Networking network;
AlarmChecker alarmChecker;
Readings readings;

/* ======== Setup ======== */
void setup() {
    Serial.begin(9600);
    SPI.begin(); 
//    mfrc522.PCD_Init(); 
    
    // Test network functions
    network.AddMessageToQueue(network.MakeAlarmMessage('1', 1, 1, 1, '1'), 111);
    network.AddMessageToQueue(network.MakeAlarmMessage('2', 2, 2, 2, '2'), 222);
    network.AddMessageToQueue(network.MakeAlarmMessage('3', 3, 3, 3, '3'), 333);
    network.AddMessageToQueue(network.MakeAlarmMessage('4', 4, 4, 4, '4'), 444);
    network.CheckAlarmMessageQueue();
    network.CheckAlarmMessageQueue();
    network.ResetMessageDelay();
    network.CheckAlarmMessageQueue();
    network.CheckAlarmMessageQueue();
    network.CheckAlarmMessageQueue();
    network.ResetMessageDelay();
    network.CheckAlarmMessageQueue();
    network.ResetMessageDelay();
    network.CheckAlarmMessageQueue();
    network.ResetMessageDelay();
    network.CheckAlarmMessageQueue();
}

/* ======== Loop ======== */
void loop() {
    // Test for PIR
    alarmLight.SetLight(pir.Read());

    // Print data from other sensors
    Serial.println("======= LDR =======");
    Serial.println(ldr.Read());
    Serial.println("======= Ultrasonic ======="); 
    Serial.println(ultrasonic.ReadMicroseconds());
    Serial.println(ultrasonic.ReadCM());
    Serial.println("======= RFID =======");
//    Serial.println(ReadRFID());
    Serial.println("======= TIME =======");
    time.PrintTimeTwoSecFormat(time.GetSystemTimeTwoSecFormat());

    delay(500);
}

/* ======== Non-class functions ======== */

// Function that reads from the RFID card reader if an RFID card is present
// TODO: Move to own class & verification method to only allow verified cards
//bool ReadRFID(){ return mfrc522.PICC_IsNewCardPresent(); }
