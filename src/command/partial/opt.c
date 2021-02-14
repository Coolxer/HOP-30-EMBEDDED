#include "command/partial/opt.h"

#include <string.h>

void opt_init()
{
    strcpy((void *)OPT.SETUP_SPEED, "ses\0");
    strcpy((void *)OPT.SWITCH, "sth\0");
    strcpy((void *)OPT.MOVE, "mov\0");
    strcpy((void *)OPT.HOME, "hom\0");
    strcpy((void *)OPT.PROCESS, "pro\0");

    strcpy((void *)OPT.PAUSE, "pau\0");
    strcpy((void *)OPT.RESUME, "res\0");
    strcpy((void *)OPT.STOP, "sto\0");
}