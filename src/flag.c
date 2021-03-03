#include "flag.h"

volatile uint8_t ENDSTOP_CLICKED = 0;
volatile uint8_t STEPPER_FINISHED = 0;
volatile uint8_t PROCESS_FORWARD = 0;

volatile uint8_t BUFFER_EMPTY;
volatile uint8_t TRANSFER_COMPLETE = 1;

void flag_init()
{
    ENDSTOP_CLICKED = 0;
    STEPPER_FINISHED = 0;

    PROCESS_FORWARD = 0;

    BUFFER_EMPTY = 1;
    TRANSFER_COMPLETE = 1;
}