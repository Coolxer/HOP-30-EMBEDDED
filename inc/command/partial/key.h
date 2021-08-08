#ifndef KEY_H
#define KEY_H

#include "command/partial/part.h"

typedef struct
{
    uint8_t INDEX[PART_LENGTH],
        OPERATION[PART_LENGTH],

        STEPPER[PART_LENGTH],
        ENDSTOP[PART_LENGTH],

        STATE[PART_LENGTH],
        SPEED[PART_LENGTH],
        ACCELERATION[PART_LENGTH],
        WAY[PART_LENGTH],
        DIRECTION[PART_LENGTH],

        RESPONSE[PART_LENGTH],
        CODE[PART_LENGTH];
} key;

extern key KEY;

void key_init();

#endif // KEY_H
