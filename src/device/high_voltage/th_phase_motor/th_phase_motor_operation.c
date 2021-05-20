#include "device/high_voltage/th_phase_motor/partial/th_phase_motor_operation.h"

void th_phase_motor_switch(HVDevice *thpMotor, uint8_t *state, uint8_t *EMPTY1)
{
    high_voltage_device_switch(thpMotor, state);
}