#ifndef OPT_H
#define OPT_H

#include "command/partial/part.h"

typedef struct
{
    uint8_t CONFIGURE_STEPPER[PART_LENGTH],

        SWITCH_STEPPER[PART_LENGTH],
        MOVE_STEPPER[PART_LENGTH],

        PAUSE_STEPPER[PART_LENGTH],
        RESUME_STEPPER[PART_LENGTH],
        STOP_STEPPER[PART_LENGTH],

        SWITCH_POMP[PART_LENGTH],
        SWITCH_TH_PHASE_MOTOR[PART_LENGTH],

        CONFIGURE_PROCESS[PART_LENGTH],
        INIT_PROCESS[PART_LENGTH],

        PAUSE_PROCESS[PART_LENGTH],
        RESUME_PROCESS[PART_LENGTH],
        STOP_PROCESS[PART_LENGTH],

        GET_ALL_STATES[PART_LENGTH]; // STEPPERS ENDSTOPS TH_PHASE_MOTOR POMP
} opt;

extern opt OPT;

void opt_init();

#endif // OPT_H