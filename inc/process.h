#ifndef PROCESS_H
#define PROCESS_H

#include "device/device_manager.h"

enum ProcessState
{
    NONE = 0,
    FORWARD = 1,
    BACKWARD = 2
};

extern volatile enum ProcessState PROCESSING;

// validates process input value, returns error code or 0 if not error
uint8_t process_validate(uint8_t *direction);

void process_init(uint8_t *idx, uint8_t direction); // inits process
void process_reverse();                             //  reverses direction on "half" process,

#endif // PROCESS_H