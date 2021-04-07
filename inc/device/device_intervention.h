#ifndef DEVICE_OPERATION_H
#define DEVICE_OPERATION_H

#include "device/device_manager.h"

void intervene_process(void (*intervention)(Stepper *)); // pause / resume / stop process
void intervene_all(void (*intervention)(Stepper *));     // pause / resume / stop all steppers

#endif // DEVICE_OPERATION_H
