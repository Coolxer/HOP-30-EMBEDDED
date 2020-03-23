#include "keys.h"

#include <string.h>

void keys_init()
{
    strcpy((void*)KEYS.OPERATION, "opt\0");
    strcpy((void*)KEYS.INDEX, "idx\0");
    strcpy((void*)KEYS.STEPPER, "spp\0");
    strcpy((void*)KEYS.ENDSTOP, "end\0");
    strcpy((void*)KEYS.SPEED, "spd\0");
    strcpy((void*)KEYS.STEPS, "stp\0");
    strcpy((void*)KEYS.MICROSTEPPING, "msp\0");
    strcpy((void*)KEYS.STEPPER_STATE, "stt\0");
    strcpy((void*)KEYS.DIRECTION, "dir\0");

    
    strcpy((void*)KEYS.RESPONSE, "res\0");
    strcpy((void*)KEYS.CODE, "cod\0");
    strcpy((void*)KEYS.VALUE, "val\0");
}