#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

enum ProcessState
{
    NONE = 0,
    FORWARD = 1,
    BACKWARD = 2,
    HALTED = 3
};

extern volatile enum ProcessState PROCESS_STATE;
extern volatile enum ProcessState PROCESS_PREVIOUS_STATE;

extern volatile uint8_t COOLANT_ENABLE;

extern volatile uint8_t PROCESS_CONFIGURED;

#endif // PROCESS_H