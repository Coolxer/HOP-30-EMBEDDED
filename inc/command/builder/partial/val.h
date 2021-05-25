#ifndef VAL_H
#define VAL_H

#include <stdint.h>

typedef struct
{
    uint8_t PROCESS[4], // stepper process's group
        ALL[4],         // stepper all's group

        LIMIT[4], // using in move
        NONE[4];  // using with acceleration (if not wanna acceleration)
} val;

extern val VAL;

void val_init();

#endif // VAL_H