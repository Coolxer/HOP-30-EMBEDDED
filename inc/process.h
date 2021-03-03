#ifndef PROCESS_H
#define PROCESS_H

#include "device/device_manager.h"

void process_init(uint8_t *idx, uint8_t direction); // inits process
void process_reverse();                             // "half" process, reversing direction

// validates process input value, returns error code or 0 if not error
uint8_t process_validate(uint8_t *direction);

#endif // PROCESS_H