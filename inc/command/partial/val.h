#ifndef VAL_H
#define VAL_H

#include "command/partial/part.h"

typedef struct
{
    uint8_t
        LIMIT[PART_LENGTH], // using in move
        NONE[PART_LENGTH];  // using with acceleration (if not wanna acceleration)
} val;

extern val VAL;

void val_init();

#endif // VAL_H