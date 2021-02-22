#include "flag.h"

volatile uint8_t ENDSTOP_CLICKED = 0;
volatile uint8_t STEPPER_FINISHED = 0;
volatile uint8_t PROCESS_FORWARD = 0;

void flag_init()
{
    ENDSTOP_CLICKED = 0;
    STEPPER_FINISHED = 0;

    // mean the process forward moving is not in progress, so it's backward or process is not currently run
    PROCESS_FORWARD = 0;
}