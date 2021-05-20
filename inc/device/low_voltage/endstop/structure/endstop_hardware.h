#ifndef ENDSTOP_HARDWARE_H
#define ENDSTOP_HARDWARE_H

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t irq;
} Hardware;

Hardware endstop_hardware_init(GPIO_TypeDef *port, uint16_t pin, uint8_t irq);

/* PRIVATE */ //void endstop_setupGpio(Hardware *hardware); // setups gpio for endstop

#endif // ENDSTOP_HARDWARE_H