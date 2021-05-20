#include "device/high_voltage/th_phase_motor/partial/th_phase_motor_setup.h"

void th_phase_motor_init(HVDevice *thpMotor, GPIO_TypeDef *port, uint16_t pin)
{
    high_voltage_device_init(thpMotor, port, pin);
}