#ifndef OPT_H
#define OPT_H

#include <stdint.h>

typedef struct
{
    uint8_t CONFIGURE[4],

        SWITCH_STEPPER[4],
        SWITCH_POMP[4],
        SWITCH_TH_PHASE_MOTOR[4],

        MOVE[4],
        PROCESS[4],

        PAUSE[4],
        RESUME[4],
        STOP[4],

        GET_STEPPER_STATE[4],
        GET_POMP_STATE[4],
        GET_TH_PHASE_MOTOR_STATE[4],
        GET_ENDSTOP_STATE[4];
} opt;

extern opt OPT;

void opt_init();

#endif // OPT_H