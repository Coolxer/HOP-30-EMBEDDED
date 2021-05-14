#include "device/th_phase_motor/partial/th_phase_motor_setup.h"

void th_phase_motor_setupGpio(Th_phase_motor *motor)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = motor->pin;
    gpio.Mode = GPIO_MODE_OUTPUT_OD;
    gpio.Pull = GPIO_PULLDOWN;

    HAL_GPIO_Init((GPIO_TypeDef *)motor->port, &gpio);

    HAL_GPIO_WritePin(motor->port, motor->pin, GPIO_PIN_RESET);
}

void th_phase_motor_init(Th_phase_motor *motor, GPIO_TypeDef *port, uint16_t pin)
{
    motor->port = port;
    motor->pin = pin;

    th_phase_motor_setupGpio(motor);
}