#ifndef KEYS_H
#define KEYS_H

#include <stdint.h> 

struct keys
{
    uint8_t OPERATION[4],
            INDEX[4],
            STEPPER[4],
            ENDSTOP[4],
            SPEED[4],
            STEPS[4],
            MICROSTEPPING[4],
            STEPPER_STATE[4],
            DIRECTION[4],

            RESPONSE[4],
            CODE[4],
            VALUE[4];
}KEYS;

void keys_init();

#endif // KEYS_H





