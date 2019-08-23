#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stepper.h"

#define DEVICES_COUNT 2

extern struct Stepper devices[DEVICES_COUNT];
extern struct Stepper *current;

void device_manager_init();
void device_manager_deinit();
void device_manager_set_current(uint8_t *name);
struct Stepper *device_manager_current();

#endif // DEVICE_MANAGER_H
