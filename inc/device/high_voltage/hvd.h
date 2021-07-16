#ifndef HVD_H
#define HVD_H

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t *state;
} HVD;

/* PRIVATE */ //void hvd_setupGpio(HVD *hvd);
void hvd_init(HVD *hvd, GPIO_TypeDef *port, uint16_t pin);
void hvd_deinit(HVD *hvd);

void hvd_switch(HVD *hvd, uint8_t *state);

uint8_t *hvd_getState(HVD *hvd);

#endif // HVD_H
