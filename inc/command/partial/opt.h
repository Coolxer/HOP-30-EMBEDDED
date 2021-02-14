#ifndef OPT_H
#define OPT_H

#include <stdint.h>

struct opt
{
    uint8_t SETUP_SPEED[4],
        SWITCH[4],
        MOVE[4],
        HOME[4],
        PROCESS[4],

        PAUSE[4],
        RESUME[4],
        STOP[4];
} OPT;

void opt_init();

#endif // OPT_H