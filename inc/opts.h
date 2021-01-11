#ifndef OPTS_H
#define OPTS_H

#include <stdint.h>

struct opts
{
    uint8_t SETUP_SPEED[4],
        GET_STATE[4],
        SWITCH[4],
        MOVE[4],
        HOME[4],
        PROCESS[4],

        PAUSE[4],
        RESUME[4],
        STOP[4];
} OPTS;

void opts_init();

#endif // OPTS_H