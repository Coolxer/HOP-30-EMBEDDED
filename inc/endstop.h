#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "device.h"

#include "stepper.h"

typedef struct 
{
    Device device;
    Stepper *parent_stepper;

    uint32_t port;        
    uint16_t pin;

    uint8_t ext;

    uint8_t clicked;
}Endstop;

Endstop *endstop;

Endstop *endstop_init(Stepper *_stepper, uint8_t *_name, uint32_t _port, uint8_t _ext, uint16_t _pin);
void endstop_deinit();
void endstop_setup_gpio();

uint8_t endstop_clicked();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif // DIVIDER_STEPPER_H
