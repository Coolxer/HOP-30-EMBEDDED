#ifndef OPT_H
#define OPT_H

#include <stdint.h>

typedef struct
{
    uint8_t CONFIGURE_STEPPER[4],

        SWITCH_STEPPER[4],
        SWITCH_POMP[4],
        SWITCH_TH_PHASE_MOTOR[4],

        MOVE_STEPPER[4],
        PROCESS_ALL[4],

        PAUSE_STEPPER[4],
        RESUME_STEPPER[4],
        STOP_STEPPER[4],

        GET_STATE_OF_STEPPER[4],
        GET_STATE_OF_POMP[4],
        GET_STATE_OF_TH_PHASE_MOTOR[4],
        GET_STATE_OF_ENDSTOP[4];
} opt;

extern opt OPT;

void opt_init();

#endif // OPT_H