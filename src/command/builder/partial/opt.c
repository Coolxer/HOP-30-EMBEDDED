#include "command/builder/partial/opt.h"

#include <string.h>

opt OPT = {0};

void opt_init()
{
    strcpy((void *)OPT.CONFIGURE_STEPPER, "cfg\0");

    strcpy((void *)OPT.SWITCH_STEPPER, "sws\0");
    strcpy((void *)OPT.SWITCH_POMP, "swp\0");
    strcpy((void *)OPT.SWITCH_TH_PHASE_MOTOR, "swm\0");

    strcpy((void *)OPT.MOVE_STEPPER, "mov\0");
    strcpy((void *)OPT.PROCESS_ALL, "pro\0");

    strcpy((void *)OPT.PAUSE_STEPPER, "pau\0");
    strcpy((void *)OPT.RESUME_STEPPER, "res\0");
    strcpy((void *)OPT.STOP_STEPPER, "sto\0");

    strcpy((void *)OPT.GET_STATE_OF_STEPPER, "gss\0");
    strcpy((void *)OPT.GET_STATE_OF_POMP, "gsp\0");
    strcpy((void *)OPT.GET_STATE_OF_TH_PHASE_MOTOR, "gst\0");
    strcpy((void *)OPT.GET_STATE_OF_ENDSTOP, "gse\0");
}