#ifndef TH_PHASE_MOTOR_SETUP_H
#define TH_PHASE_MOTOR_SETUP_H

#include "device/th_phase_motor/th_phase_motor.h"

void th_phase_motor_init(Th_phase_motor *motor, GPIO_TypeDef *port, uint16_t pin);

/* PRIVATE */ //void th_phase_motor_setupGpio(Th_phase_motor *motor);

#endif // TH_PHASE_MOTOR_SETUP_H
