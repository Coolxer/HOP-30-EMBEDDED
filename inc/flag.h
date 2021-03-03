#ifndef FLAG_H
#define FLAG_H

#include <stdint.h>

extern volatile uint8_t ENDSTOP_CLICKED;
extern volatile uint8_t STEPPER_FINISHED;
extern volatile uint8_t PROCESS_FORWARD;

extern volatile uint8_t BUFFER_EMPTY;
extern volatile uint8_t TRANSFER_COMPLETE;

void flag_init(); // set default flags states

#endif // FLAG_H