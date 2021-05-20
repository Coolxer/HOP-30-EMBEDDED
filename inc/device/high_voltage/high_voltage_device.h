#ifndef HIGH_VOLTAGE_DEVICE_H
#define HIGH_VOLTAGE_DEVICE_H

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t state;
} HVDevice;

/* PRIVATE */ //void device_setupGpio(hvDevice *hvDevice);
void high_voltage_device_init(HVDevice *hvDevice, GPIO_TypeDef *port, uint16_t pin);
void high_voltage_device_switch(HVDevice *hvDevice, uint8_t *state);

#endif // HIGH_VOLTAGE_DEVICE_H
