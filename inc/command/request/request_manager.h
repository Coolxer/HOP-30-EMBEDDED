#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

#include <stdint.h>

// 10 STEPS TO PROCESS REQUEST
/*
    STEP 1: TRUNCATE REQUEST
    STEP 2: VALIDATE TRUNCATED REQUEST LENGTH
    STEP 3: EXPLODE FOR PAIRS KEY:VALUE
    STEP 4: GENERAL VALIDATION (RECORDS, INDEX, OPERATION CHECKS)
    STEP 5: GET INDEX AND OPERATION TYPE
    STEP 6: SCHRINK DATA TO LEAVE ONLY NEEDED DATA (REMOVE GATHERED INDEX AND OPERATION RECORDS)
    STEP 7: CHECK IF OPERATION TYPE IS KNOWN AND PREPARE DATA FOR NEXT STEPS (DEPEND ON OPERATION)
    STEP 8: VALIDATE REQUEST KEYS
    STEP 9: VALIDATE REQUEST VALUES AND ENVIRONMENT STATES
    STEP 10: EXECUTE REQUEST
*/

uint8_t *request_process(uint8_t *request);

#endif // REQUEST_MANAGER_H