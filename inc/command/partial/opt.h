#ifndef OPT_H
#define OPT_H

#include <stdint.h>

typedef struct
{
    uint8_t CONFIGURE_STEPPER[4],
        CONFIGURE_PROCESS[4],

        SWITCH_STEPPER[4],
        SWITCH_POMP[4],
        SWITCH_TH_PHASE_MOTOR[4],

        MOVE_STEPPER[4],

        PAUSE_STEPPER[4],
        RESUME_STEPPER[4],
        STOP_STEPPER[4],

        PAUSE_PROCESS[4],
        RESUME_PROCESS[4],
        STOP_PROCESS[4],

        INIT_PROCESS[4],

        GET_ALL_STATES[4]; // STEPPERS ENDSTOPS TH_PHASE_MOTOR POMP
} opt;

extern opt OPT;

void opt_init();

#endif // OPT_H