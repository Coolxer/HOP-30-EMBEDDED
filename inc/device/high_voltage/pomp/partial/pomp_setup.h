#ifndef POMP_SETUP_H
#define POMP_SETUP_H

#include "device/high_voltage/high_voltage_device.h"

void pomp_init(HVDevice *pomp, GPIO_TypeDef *port, uint16_t pin);

#endif // POMP_SETUP_H
