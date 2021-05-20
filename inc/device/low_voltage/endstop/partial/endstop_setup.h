#ifndef ENDSTOP_SETUP_H
#define ENDSTOP_SETUP_H

#include "device/low_voltage/endstop/endstop.h"

void endstop_init(Endstop *endstop, uint8_t *name, GPIO_TypeDef *port, uint16_t pin, uint8_t irq); // endstop "constructor" function
void endstop_deinit(Endstop *endstop);                                                             // disables IRQ

#endif // ENDSTOP_SETUP_H
