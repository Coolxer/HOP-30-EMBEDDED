#ifndef VAL_H
#define VAL_H

#include <stdint.h>

typedef struct
{
    uint8_t PROCESS[4],
        ALL[4];

} val;

extern val VAL;

void val_init();

#endif // VAL_H