#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <stdbool.h>

#include "stepper.h"
#include "endstop.h"

#define DEVICES_COUNT 3

Device *devices[DEVICES_COUNT];

Device *current;

void device_manager_init(); // sets devices parameters and reset current device
void device_manager_deinit(); // frees memory for current device
bool device_manager_set_current(uint8_t *name); // sets current device by name, if device name is not recognized, returns FALSE

#endif // DEVICE_MANAGER_H
