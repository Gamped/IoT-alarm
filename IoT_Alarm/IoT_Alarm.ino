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
MFRC522 mfrc522(RFID_SDA, RFID_RST);
AlarmTime time;
Networking network;
AlarmChecker alarmChecker;
Readings readings;

/* ======== Setup ======== */
void setup() {
    Serial.begin(9600);
    SPI.begin(); 
    mfrc522.PCD_Init(); 
    InitReadings();
    alarmLight.SetLight(true);
    delay(2000);
    alarmLight.SetLight(false);
    for (int i = 0; i < 75; i++){
        network.AddMessageToQueue(network.MakeAlarmMessage('a', 1, 1, 1, '1'));
    }
    
    MeasureFunction(75);
}

/* ======== Loop ======== */
void loop() {
    char result = alarmChecker.CheckForAlarm(&readings,
                               ultrasonic.ReadCM(),
                               pir.Read(),
                               ldr.Read());
    if (result != 'A'){
        Serial.println("___!ALARM!___");
        Serial.println(result);
        alarmLight.SetLight(true);
    } else alarmLight.SetLight(false);
    ReadRFID();
    delay(300);
}

/* ======== Non-class functions ======== */

// Function that reads from the RFID card reader if an RFID card is present
// TODO: Move to own class & verification method to only allow verified cards
bool ReadRFID(){ return mfrc522.PICC_IsNewCardPresent(); }

// Function used to initialize values of readings
void InitReadings(){
    alarmLight.SetLight(true);
    for (int i = 0; i < (int)READING_LIST_SIZE; i++){
        readings.AddReadingLDR(ldr.Read());
        readings.AddReadingUltrasonic(ultrasonic.ReadCM());
        delay(200);
    }
    alarmLight.SetLight(false);
}

void MeasureFunction(int times){
    unsigned long highestTime = 0, startTime = 0, time = 0;
    unsigned long save[times];

    for (int i = 0; i < times; i++){
        startTime = millis();

        // Function to take time off:
        network.CheckAlarmMessageQueue();
        network.ResetMessageDelay();
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
