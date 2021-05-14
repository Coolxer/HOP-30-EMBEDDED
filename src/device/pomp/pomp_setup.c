#include "device/pomp/partial/pomp_setup.h"

void pomp_setupGpio(Pomp *pomp)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = pomp->pin;
    gpio.Mode = GPIO_MODE_OUTPUT_OD;
    gpio.Pull = GPIO_PULLDOWN;

    HAL_GPIO_Init((GPIO_TypeDef *)pomp->port, &gpio);

    HAL_GPIO_WritePin(pomp->port, pomp->pin, GPIO_PIN_RESET);
}

void pomp_init(Pomp *pomp, GPIO_TypeDef *port, uint16_t pin)
{
    pomp->port = port;
    pomp->pin = pin;

    pomp_setupGpio(pomp);
}