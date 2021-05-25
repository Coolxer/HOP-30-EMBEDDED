#include "command/partial/opt.h"

#include <string.h>

opt OPT;

void opt_init()
{
    strcpy((void *)OPT.CONFIGURE_STEPPER, "cfg\0");

    strcpy((void *)OPT.SWITCH_STEPPER, "sws\0");
    strcpy((void *)OPT.SWITCH_POMP, "swp\0");
    strcpy((void *)OPT.SWITCH_TH_PHASE_MOTOR, "swm\0");

    strcpy((void *)OPT.MOVE_STETPPER, "mov\0");
    strcpy((void *)OPT.PROCESS_ALL, "pro\0");

    strcpy((void *)OPT.PAUSE_STEPPER, "pau\0");
    strcpy((void *)OPT.RESUME_STEPPER, "res\0");
    strcpy((void *)OPT.STOP_STEPPER, "sto\0");

    strcpy((void *)OPT.GET_STATE_OF_STEPPER, "gss\0");
    strcpy((void *)OPT.GET_STATE_OF_POMP, "gps\0");
    strcpy((void *)OPT.GET_STATE_OF_TH_PHASE_MOTOR, "gms\0");
    strcpy((void *)OPT.GET_STATE_OF_ENDSTOP, "ges\0");
}