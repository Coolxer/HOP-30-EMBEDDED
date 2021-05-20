#ifndef TH_PHASE_MOTOR_OPERATION_H
#define TH_PHASE_MOTOR_OPERATION_H

#include "device/high_voltage/high_voltage_device.h"

void th_phase_motor_switch(HVDevice *thpMotor, uint8_t *state, uint8_t *EMPTY1);

#endif // TH_PHASE_MOTOR_OPERATION_H
