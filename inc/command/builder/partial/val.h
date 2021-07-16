#ifndef VAL_H
#define VAL_H

#include <stdint.h>

typedef struct
{
    uint8_t
        LIMIT[4], // using in move
        NONE[4];  // using with acceleration (if not wanna acceleration)
} val;

extern val VAL;

void val_init();

#endif // VAL_H