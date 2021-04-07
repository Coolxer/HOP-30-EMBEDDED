#ifndef PROCESS_H
#define PROCESS_H

#include "device/device_manager.h"

/* Process State
    * 0 - LINEAR (X, Y, Z)
    * 1 - CIRCULAR (W, K)
*/
enum ProcessState
{
    NONE = 0,
    FORWARD = 1,
    BACKWARD = 2
};

extern volatile enum ProcessState PROCESSING;

void process_init(uint8_t *idx, uint8_t direction); // inits process
void process_reverse();                             //  reverses direction on "half" process,

// validates process input value, returns error code or 0 if not error
uint8_t process_validate(uint8_t *direction);

#endif // PROCESS_H