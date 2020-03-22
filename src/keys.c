#include "keys.h"

#include <string.h>

void keys_init()
{
    strcpy(KEYS.OPERATION, "opt\0");
    strcpy(KEYS.INDEX, "idx\0");
    strcpy(KEYS.STEPPER, "spp\0");
    strcpy(KEYS.ENDSTOP, "end\0");
    strcpy(KEYS.SPEED, "spd\0");
    strcpy(KEYS.STEPS, "stp\0");
    strcpy(KEYS.MICROSTEPPING, "msp\0");
    strcpy(KEYS.STEPPER_STATE, "stt\0");
    strcpy(KEYS.DIRECTION, "dir\0");

    
    strcpy(KEYS.RESPONSE, "res\0");
    strcpy(KEYS.CODE, "cod\0");
    strcpy(KEYS.VALUE, "val\0");
}