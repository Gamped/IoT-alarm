/* ======== Includes ======== */
#include "PIR.h"
#include "LDR.h"
#include "Ultrasonic.h"
#include "AlarmLight.h"
#include <MFRC522.h>
#include "AlarmTime.h"
#include "Networking.h"
#include "AlarmChecker.h"
#include "Readings.h"
#include <TimerOne.h>

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
MFRC522 rfid(RFID_SDA, RFID_RST);
AlarmTime alarmTime;
Networking network;
AlarmChecker alarmChecker;
Readings readings;
bool readingPIR, interruptWait = false;
unsigned long readingUltrasonic;
int readingLDR;
char alarmType;

/* ======== Setup ======== */
void setup() {
    Serial.begin(9600);
    SPI.begin(); 
    rfid.PCD_Init();
    // Get intial measurements for Ultrasonic and LDR 
    InitReadings();
    // Set timer to every 150ms and associate function to allow to run
    Timer1.initialize(150000);
    Timer1.attachInterrupt(InterruptCalled);
}

/* ======== Loop ======== */
void loop() {
    // First minor cycle
    WaitForInterrupt();
    readingPIR = pir.Read();
    readingLDR = ldr.Read();
    readingUltrasonic = ultrasonic.ReadCM();
    alarmType = alarmChecker.CheckForAlarm(&readings,
                                           readingUltrasonic,
                                           readingPIR,
                                           readingLDR);
    if (alarmType != 'A'){
        network.AddMessageToQueue(network.MakeAlarmMessage(alarmType,
                                                           alarmTime.GetSystemTimeTwoSecFormat(),
                                                           readingLDR,
                                                           readingUltrasonic,
                                                           (char)readingPIR));
    }

    // Second minor cycle
    WaitForInterrupt();
    readingPIR = pir.Read();
    readingLDR = ldr.Read();
    network.CheckAlarmMessageQueue();
    ReadRFID();
    alarmType = alarmChecker.CheckForAlarm(&readings,
                                           readingUltrasonic,
                                           readingPIR,
                                           readingLDR);
    if (alarmType != 'A'){
        network.AddMessageToQueue(network.MakeAlarmMessage(alarmType,
                                                           alarmTime.GetSystemTimeTwoSecFormat(),
                                                           readingLDR,
                                                           readingUltrasonic,
                                                           (char)readingPIR));
    }
}

/* ======== Non-class functions ======== */

// Function that reads from the RFID card reader if an RFID card is present
void ReadRFID(){ 
    if (rfid.PICC_IsNewCardPresent()){
        // If it's present then reset time before next alarm can be sent
        network.ResetMessageDelay();

        // Blink to quickly indicate read
        alarmLight.SetLight(true);
        delayMicroseconds(250);
        alarmLight.SetLight(false);
    }
}

// Function used to initialize values of readings
void InitReadings(){
    alarmLight.SetLight(true);
    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        readings.AddReadingLDR(ldr.Read());
        readings.AddReadingUltrasonic(ultrasonic.ReadCM());
        delay(250);
    }
    alarmLight.SetLight(false);
}

// Function called by interrupt timer to set interruptWait
void InterruptCalled(){ interruptWait = false; }

// Function used to wait for next interrupt to happen
void WaitForInterrupt(){
    interruptWait = true;
    // Just keep "busy wait" with check
    // And make sure not interrupted during check
    for (;;){
        cli();
        if (interruptWait == false){
            sei(); 
            return; 
        }
        sei();
        delayMicroseconds(1);
    }
}

// Function used to measure worst case computation time of functions
void MeasureFunction(int times){
    unsigned long highestTime = 0, startTime = 0, time = 0;
    unsigned long save[times];

    for (int i = 0; i < times; i++){
        startTime = millis();

        // Function to take time off:

        // ========================

        time = millis() - startTime;
        if (time > highestTime){ highestTime = time; }
        save[i] = time;
    }

    for (unsigned long i: save){
        Serial.print(i);
        Serial.print(",");
    }
    Serial.println("");
    Serial.print("Worst time: ");
    Serial.println(highestTime);
}
