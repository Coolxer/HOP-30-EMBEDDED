#ifndef VAL_H
#define VAL_H

#include <stdint.h>

typedef struct
{
    uint8_t PROCESS[4], // using in intervention
        ALL[4],         // using in intervention
        LIMIT[4],       // using in move
        NONE[4];        // using with acceleration (if not acceleration)

} val;

extern val VAL;

void val_init();

#endif // VAL_H