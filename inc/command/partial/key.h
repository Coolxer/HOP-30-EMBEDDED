#ifndef KEY_H
#define KEY_H

#include <stdint.h>

typedef struct
{
    uint8_t INDEX[4],
        OPERATION[4],

        STEPPER[4],
        ENDSTOP[4],

        SPEED[4],
        ACCELERATION[4],
        WAY[4],
        STATE[4],
        DIRECTION[4],

        RESPONSE[4],
        CODE[4];
} key;

extern key KEY;

void key_init();

#endif // KEY_H
