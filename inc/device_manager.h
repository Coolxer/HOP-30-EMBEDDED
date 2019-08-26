#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <stdint.h> // includes uint8_t data type
//#include "stm32f4xx_hal.h"
#include "stepper.h"

#define DEVICES_COUNT 2 // count of supported devices

struct Stepper devices[DEVICES_COUNT]; // array of desvices
struct Stepper *current; // pointer to the current operating device

void device_manager_init(); // sets devices parameters and reset current device
void device_manager_deinit(); // frees memory for current device
void device_manager_set_current(uint8_t *name); // sets current device by name
struct Stepper *device_manager_current(); // returns pointer to current device

#endif // DEVICE_MANAGER_H
