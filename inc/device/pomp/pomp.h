#ifndef POMP_H
#define POMP_H

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} Pomp;

#endif // POMP_H
