#include "command/partial/opt.h"

#include <string.h>

opt OPT = {0};

void opt_init()
{
    strcpy((void *)OPT.CONFIGURE_STEPPER, "cfs\0");
    strcpy((void *)OPT.CONFIGURE_PROCESS, "cfp\0");

    strcpy((void *)OPT.SWITCH_STEPPER, "sws\0");
    strcpy((void *)OPT.SWITCH_POMP, "swp\0");
    strcpy((void *)OPT.SWITCH_TH_PHASE_MOTOR, "swm\0");

    strcpy((void *)OPT.MOVE_STEPPER, "mov\0");

    strcpy((void *)OPT.PAUSE_STEPPER, "pas\0");
    strcpy((void *)OPT.RESUME_STEPPER, "res\0");
    strcpy((void *)OPT.STOP_STEPPER, "sts\0");

    strcpy((void *)OPT.PAUSE_PROCESS, "pap\0");
    strcpy((void *)OPT.RESUME_PROCESS, "rep\0");
    strcpy((void *)OPT.STOP_PROCESS, "stp\0");

    strcpy((void *)OPT.INIT_PROCESS, "inp\0");

    strcpy((void *)OPT.GET_ALL_STATES, "gas\0");
}