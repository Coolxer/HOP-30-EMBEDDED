#include "command/partial/opt.h"

#include <string.h>

opt OPT;

void opt_init()
{
    strcpy((void *)OPT.CONFIGURE, "cfg\0");
    strcpy((void *)OPT.SWITCH, "sth\0");
    strcpy((void *)OPT.MOVE, "mov\0");
    strcpy((void *)OPT.PROCESS, "pro\0");

    strcpy((void *)OPT.PAUSE, "pau\0");
    strcpy((void *)OPT.RESUME, "res\0");
    strcpy((void *)OPT.STOP, "sto\0");
}