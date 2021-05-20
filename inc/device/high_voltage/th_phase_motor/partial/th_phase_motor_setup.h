#ifndef TH_PHASE_MOTOR_SETUP_H
#define TH_PHASE_MOTOR_SETUP_H

#include "device/high_voltage/high_voltage_device.h"

void th_phase_motor_init(HVDevice *pomp, GPIO_TypeDef *port, uint16_t pin);

#endif // TH_PHASE_MOTOR_SETUP_H
