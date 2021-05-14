#include "device/th_phase_motor/partial/th_phase_motor_operation.h"

void th_phase_motor_switch(Th_phase_motor *motor, uint8_t *state, uint8_t *EMPTY1)
{
    uint8_t st = convertStrToBoolean(state);

    if (HAL_GPIO_ReadPin(motor->port, motor->pin) != st)
        HAL_GPIO_WritePin((GPIO_TypeDef *)motor->port, motor->pin, st);
}