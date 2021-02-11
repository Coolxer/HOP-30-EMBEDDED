#include "flags.h"

void flags_init()
{
    ENDSTOP_CLICKED = 0;
    STEPPER_FINISHED = 0;

    // mean the process forward moving is not in progress, so it's backward or process is not currently run
    PROCESS_FORWARD = 0;
}