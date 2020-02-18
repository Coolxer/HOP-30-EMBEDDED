#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "stepper.h"

typedef struct 
{
    uint8_t name[2];                            // 2-characters name
    Stepper *parentStepper;                     // pointer to parent stepper to which the endstop will affect

    uint32_t port;                              // gpio port, where the pin is connected        
    uint16_t pin;                               // endstop pin

    uint8_t irq;                                // external interrupt name pointer

    uint8_t clicked;                            // endstop pin status (released = 0, clicked = 1)
}Endstop;

Endstop *endstop;                               // endstop pointer, using to make operations on actual selected endstop

void endstop_init(Endstop *endstop, uint8_t *name, Stepper *parentStepper, uint32_t port, uint16_t pin, uint8_t irq); // endstop "constructor" function
void endstop_deinit(Endstop *endstop);          // disables IRQ

void endstop_setupGpio(Endstop *endstop);      // setups gpio for endstop

uint8_t endstop_isClicked(Endstop *endstop);

#endif // ENDSTOP_H
