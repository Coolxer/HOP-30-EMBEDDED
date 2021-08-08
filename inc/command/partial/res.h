#ifndef RES_H
#define RES_H

#include "command/partial/part.h"

typedef struct
{
    uint8_t ERROR[PART_LENGTH],
        PASSED[PART_LENGTH],
        FINISHED[PART_LENGTH],
        VALUE[PART_LENGTH];
} res;

extern res RES;

extern uint8_t *ZERO_INDEX;
extern uint8_t *SHUTDOWN_REQUEST;
extern uint8_t *SHUTDOWN_RESPONSE;

void res_init();

#endif // RES_H