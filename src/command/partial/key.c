#include "command/partial/key.h"

#include <string.h>

key KEY;

void key_init()
{
    strcpy((void *)KEY.INDEX, "idx\0");
    strcpy((void *)KEY.OPERATION, "opt\0");

    strcpy((void *)KEY.STEPPER, "spp\0");
    strcpy((void *)KEY.ENDSTOP, "end\0");

    strcpy((void *)KEY.SPEED, "spd\0");
    strcpy((void *)KEY.ACCELERATION, "acc\0");
    strcpy((void *)KEY.WAY, "way\0");
    strcpy((void *)KEY.STATE, "stt\0");
    strcpy((void *)KEY.DIRECTION, "dir\0");

    strcpy((void *)KEY.RESPONSE, "res\0");
    strcpy((void *)KEY.CODE, "cod\0");
}