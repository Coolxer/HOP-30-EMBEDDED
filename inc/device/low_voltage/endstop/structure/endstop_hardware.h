#ifndef ENDSTOP_HARDWARE_H
#define ENDSTOP_HARDWARE_H

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t irq;
} Hardwaree;

/* PRIVATE */ //void endstop_setupGpio(Hardwaree *hardware); // setups gpio for endstop

Hardwaree endstop_hardware_init(GPIO_TypeDef *port, uint16_t pin, uint8_t irq);

#endif // ENDSTOP_HARDWARE_H