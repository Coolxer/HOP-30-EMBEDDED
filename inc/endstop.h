#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "stm32f4xx_hal.h"

struct Endstop
{
    uint8_t name[2]; // 2-character endstop name (id)

    uint32_t port;        
    uint16_t pin;

    uint8_t ext;

    uint8_t clicked;
};

void endstop_init(struct Endstop* e, uint8_t *_name, uint32_t _port, uint8_t _ext, uint16_t _pin);
void endstop_setup_gpio(struct Endstop *e);

uint8_t endstop_clicked(struct Endstop *e);

#endif // DIVIDER_STEPPER_H
