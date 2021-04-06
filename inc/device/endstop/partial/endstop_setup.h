#ifndef ENDSTOP_SETUP_H
#define ENDSTOP_SETUP_H

#include "device/endstop/endstop.h"

void endstop_init(Endstop *endstop, GPIO_TypeDef *port, uint16_t pin, uint8_t irq); // endstop "constructor" function
void endstop_deinit(Endstop *endstop);                                              // disables IRQ

/* PRIVATE */ //void endstop_setupGpio(Endstop *endstop); // setups gpio for endstop

#endif // ENDSTOP_SETUP_H
