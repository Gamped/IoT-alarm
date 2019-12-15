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
bool readingPIR;
unsigned long readingUltrasonic;
int readingLDR;
char alarmResult;

/* ======== Setup ======== */
void setup() {
    Serial.begin(9600);
    SPI.begin(); 
    mfrc522.PCD_Init(); 
    InitReadings();
}

/* ======== Loop ======== */
void loop() {
    // Make readings
    readingPIR = pir.Read();
    readingUltrasonic = ultrasonic.ReadCM();
    readingLDR = ldr.Read();
    // Check for alarm
    alarmResult = alarmChecker.CheckForAlarm(&readings, 
                                             readingUltrasonic, 
                                             readingPIR, 
                                             readingLDR);
    // If alarm then add to queue
    if (alarmResult != 'A'){
        network.AddMessageToQueue(network.MakeAlarmMessage(alarmResult, 
                                                           alarmTime.GetSystemTimeTwoSecFormat(), 
                                                           readingLDR, 
                                                           readingUltrasonic, 
                                                           (char)readingPIR));
    }
    // See if we are alowed to send message
    network.CheckAlarmMessageQueue();
    // Read RFID card
    ReadRFID();
}

/* ======== Non-class functions ======== */

// Function that reads from the RFID card reader if an RFID card is present
void ReadRFID(){ 
    if (rfid.PICC_IsNewCardPresent()){
        // If it's present then reset time before next alarm can be sent
        network.ResetMessageDelay();
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
