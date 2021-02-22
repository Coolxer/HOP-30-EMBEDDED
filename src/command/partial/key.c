#include "command/partial/key.h"

#include <string.h>

void key_init()
{
    strcpy((void *)KEY.OPERATION, "opt\0");
    strcpy((void *)KEY.INDEX, "idx\0");
    strcpy((void *)KEY.STEPPER, "spp\0");
    strcpy((void *)KEY.SPEED, "spd\0");
    strcpy((void *)KEY.WAY, "way\0");
    strcpy((void *)KEY.STEPPER_STATE, "stt\0");
    strcpy((void *)KEY.DIRECTION, "dir\0");

    strcpy((void *)KEY.RESPONSE, "res\0");
    strcpy((void *)KEY.CODE, "cod\0");
}