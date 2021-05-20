#include "device/high_voltage/high_voltage_device.h"

void high_voltage_device_setupGpio(HVDevice *hvDevice)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = hvDevice->pin;
    gpio.Mode = GPIO_MODE_OUTPUT_OD;
    gpio.Pull = GPIO_PULLDOWN;

    HAL_GPIO_Init((GPIO_TypeDef *)hvDevice->port, &gpio);

    HAL_GPIO_WritePin(hvDevice->port, hvDevice->pin, GPIO_PIN_RESET);
}

void high_voltage_device_init(HVDevice *hvDevice, GPIO_TypeDef *port, uint16_t pin)
{
    hvDevice->port = port;
    hvDevice->pin = pin;
    hvDevice->state = 0;

    high_voltage_device_setupGpio(hvDevice);
}

void high_voltage_device_switch(HVDevice *hvDevice, uint8_t *state)
{
    uint8_t st = convertStrToBoolean(state);

    if (HAL_GPIO_ReadPin(hvDevice->port, hvDevice->pin) != st)
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)hvDevice->port, hvDevice->pin, st);
        hvDevice->state = st;
    }
}