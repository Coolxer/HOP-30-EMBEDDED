#ifndef POMP_OPERATION_H
#define POMP_OPERATION_H

#include "device/high_voltage/high_voltage_device.h"

void pomp_switch(HVDevice *pomp, uint8_t *state, uint8_t *EMPTY1);

#endif // POMP_OPERATION_H
