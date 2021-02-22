#ifndef KEY_H
#define KEY_H

#include <stdint.h>

typedef struct
{
    uint8_t OPERATION[4],
        INDEX[4],
        STEPPER[4],
        SPEED[4],
        WAY[4],
        STEPPER_STATE[4],
        DIRECTION[4],

        RESPONSE[4],
        CODE[4];
} key;

extern key KEY;

void key_init();

#endif // KEY_H
