#include "command/partial/opt.h"

#include <string.h>

opt OPT;

void opt_init()
{
    strcpy((void *)OPT.CONFIGURE, "cfg\0");

    strcpy((void *)OPT.SWITCH_STEPPER, "sws\0");
    strcpy((void *)OPT.SWITCH_POMP, "swp\0");
    strcpy((void *)OPT.SWITCH_TH_PHASE_MOTOR, "swm\0");

    strcpy((void *)OPT.MOVE, "mov\0");
    strcpy((void *)OPT.PROCESS, "pro\0");

    strcpy((void *)OPT.PAUSE, "pau\0");
    strcpy((void *)OPT.RESUME, "res\0");
    strcpy((void *)OPT.STOP, "sto\0");

    strcpy((void *)OPT.GET_STEPPER_STATE, "gss\0");
    strcpy((void *)OPT.GET_POMP_STATE, "gps\0");
    strcpy((void *)OPT.GET_TH_PHASE_MOTOR_STATE, "gms\0");
    strcpy((void *)OPT.GET_ENDSTOP_STATE, "ges\0");
}