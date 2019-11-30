#define QUEUE_MAX_SIZE 3

/* 
 * ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 * NOTE: Dette vil selvfølgelig blive struktureret i forskellige filer :)
 * ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 */

/* ========================== */
/* Custom types */

typedef struct alarmMessage {
  char type;
  short timeStamp;
  long valueLDR;
  long valueUltrasonic;
  char bitmap; 
} alarmMessage_t;

typedef struct alarmMessageQueue {
  alarmMessage_t data;
  struct alarmMessageQueue *next;
} alarmMessageQueue_t;

typedef struct boolReadings {
  bool data;
  struct boolReadings *next;
} boolReadings_t;

typedef struct longReadings {
  long data;
  struct longReadings *next;
} longReadings_t;

/* ========================== */
/* Global variables */ 
//TODO: Implementer eget main loop, hvor disse er ikke er globale 
boolReadings_t *readingsPIR = NULL;
longReadings_t *readingsLDR = NULL;
longReadings_t *readingsUltrasonic = NULL;

/* ========================== */
/* Loop/Setup */

void setup() { 
  Serial.begin(9600); 
}

void loop() {
  alarmMessage_t pay = MakeAlarmPayload(2);
  PrintTime(pay.timeStamp);
  delay(500);
}

/* ========================== */
/* Alarm measurement- and check functions*/
// TODO: Find en måde at undgå copy-pasta kode her :D

// Writes a new index to the PIR readings queue, removes last index
void UpdatePIRReadings(bool reading){
  // If intializing
  if (readingsPIR == NULL){
    readingsPIR = malloc(sizeof boolReadings_t));
    readingsPIR->data = reading;
  } else {
    // Create new instance and set its data
    boolReadings_t *newEntry = malloc(sizeof boolReadings_t));
    newEntry->data = reading;

    // Switch next-references, so newEntry is the first in queue
    newEntry->next = readingsPIR;
    readingsPIR = newEntry;

    // Remove QUEUE_MAX_SIZE++th entry in list, as only QUEUE_MAX_SIZE are desired
    boolReadings_t *curr = readingsPIR;
    for (int i = 0; i < (QUEUE_MAX_SIZE - 1); i++){
      // Ensure not to work on a NULL
      if (curr->next == NULL) { 
        return; // As nothing else needs to be done
      } else { curr = curr->next; }
    }
    free(curr->next);
    curr->next = NULL;
  }
}

// Writes a new index to the LDR readings queue, removes last index
void UpdateLDRReadings(long reading){
  // If intializing
  if (readingsLDR == NULL){
    readingsLDR = malloc(sizeof(longReadings_t));
    readingsLDR->data = reading;
  } else {
    // Create new instance and set its data
    longReadings_t *newEntry = malloc(sizeof(longReadings_t));
    newEntry->data = reading;

    // Switch next-references, so newEntry is the first in queue
    newEntry->next = readingsLDR;
    readingsLDR = newEntry;

    // Remove QUEUE_MAX_SIZE++th entry in list, as only QUEUE_MAX_SIZE are desired
    longReadings_t *curr = readingsLDR;
    for (int i = 0; i < (QUEUE_MAX_SIZE - 1); i++){
      // Ensure not to work on a NULL
      if (curr->next == NULL) { 
        return; // As nothing else needs to be done
      } else { curr = curr->next; }
    }
    free(curr->next);
    curr->next = NULL;
  }
}

// Writes a new index to the Ultrasonic readings queue, removes last index
void UpdateUltrasonicReadings(long reading){
  // If intializing
  if (readingsUltrasonic == NULL){
    readingsUltrasonic = malloc(sizeof(longReadings_t));
    readingsUltrasonic->data = reading;
  } else {
    // Create new instance and set its data
    longReadings_t *newEntry = malloc(sizeof(longReadings_t));
    newEntry->data = reading;

    // Switch next-references, so newEntry is the first in queue
    newEntry->next = readingsUltrasonic;
    readingsUltrasonic = newEntry;

    // Remove QUEUE_MAX_SIZE++th entry in list, as only QUEUE_MAX_SIZE are desired
    longReadings_t *curr = readingsUltrasonic;
    for (int i = 0; i < (QUEUE_MAX_SIZE - 1); i++){
      // Ensure not to work on a NULL
      if (curr->next == NULL) { 
        return; // As nothing else needs to be done
      } else { curr = curr->next; }
    }
    free(curr->next);
    curr->next = NULL;
  }
}

/* ========================== */
/* Payload functions */

// Make payload
alarmMessage_t MakeAlarmPayload(char type){
  char bitmapStore;

  // TODO: Implement bitmap when RFID implementation is done (decision on how to handle)

  alarmMessage_t payload = {type, 
                            GetTimestamp(), 
                            readingsLDR == NULL ? 0 : readingsLDR->data, 
                            readingsUltrasonic == NULL ? 0 : readingsUltrasonic->data,
                            bitmapStore};
  return payload;
}