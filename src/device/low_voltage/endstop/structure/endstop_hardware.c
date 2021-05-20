#include "device/low_voltage/endstop/structure/endstop_hardware.h"

Hardware endstop_hardware_init(GPIO_TypeDef *port, uint16_t pin, uint8_t irq)
{
    Hardware hardware = {0};

    hardware.port = port;
    hardware.pin = pin;
    hardware.irq = irq;

    endstop_setupGpio(&hardware);

    return hardware;
}

void endstop_setupGpio(Hardware *hardware)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = hardware->pin;
    gpio.Mode = GPIO_MODE_IT_FALLING;
    gpio.Pull = GPIO_PULLUP;

    HAL_GPIO_Init((GPIO_TypeDef *)hardware->port, &gpio);

    HAL_NVIC_SetPriority(hardware->irq, 0, 0); // set priority of endstop interrupt [MOST IMPORTANT]
    HAL_NVIC_EnableIRQ(hardware->irq);         // enables external interrupt on endstop pin
}