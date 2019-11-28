/* ======== Includes ======== */
#include "PIR.h"

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

/* ======== Setup ======== */
void setup() {
    Serial.begin(9600);
    pinMode(LED_RED, OUTPUT);
}

/* ======== Loop ======== */
void loop() {
    digitalWrite(LED_RED, pir.Read());
    delay(150);
}
