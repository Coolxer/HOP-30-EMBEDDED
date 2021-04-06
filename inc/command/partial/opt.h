#ifndef OPT_H
#define OPT_H

#include <stdint.h>

typedef struct
{
    uint8_t CONFIGURE[4],
        SWITCH[4],
        MOVE[4],
        HOME[4],
        PROCESS[4],

        PAUSE[4],
        RESUME[4],
        STOP[4];
} opt;

extern opt OPT;

void opt_init();

#endif // OPT_H