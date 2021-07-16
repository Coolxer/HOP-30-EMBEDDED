#include "device/high_voltage/hvd.h"

#include "command/builder/partial/data_assistant.h"
#include <string.h>

void hvd_setupGpio(HVD *hvd)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = hvd->pin;
    gpio.Mode = GPIO_MODE_OUTPUT_OD;
    gpio.Pull = GPIO_PULLDOWN;

    HAL_GPIO_Init((GPIO_TypeDef *)hvd->port, &gpio);

    HAL_GPIO_WritePin(hvd->port, hvd->pin, GPIO_PIN_RESET);
}

void hvd_init(HVD *hvd, GPIO_TypeDef *port, uint16_t pin)
{
    hvd->port = port;
    hvd->pin = pin;
    hvd->state = 0;

    hvd_setupGpio(hvd);
}

void hvd_deinit(HVD *hvd)
{
    HAL_GPIO_DeInit(hvd->port, hvd->pin);
}

void hvd_switch(HVD *hvd, uint8_t *state)
{
    uint8_t st = convertStrToBoolean(state);

    if (HAL_GPIO_ReadPin(hvd->port, hvd->pin) != st)
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)hvd->port, hvd->pin, st);
        strcpy((void *)hvd->state, (void *)state);
    }
}

uint8_t *hvd_getState(HVD *hvd)
{
    return hvd->state;
}