#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "stepper.h"

typedef struct 
{
    uint8_t name[2];                            // 2-characters name
    Stepper *parent_stepper;                    // pointer to parent stepper to which the endstop will affect

    uint32_t port;                              // gpio port, where the pin is connected        
    uint16_t pin;                               // endstop pin

    uint8_t irq;                                // external interrupt name pointer
}Endstop;

Endstop *endstop;                               // endstop pointer, using to make operations on actual selected endstop

Endstop *endstop_init(Stepper *stepper, uint8_t *name, uint32_t port, uint8_t irq, uint16_t pin); // endstop "constructor" function
void endstop_deinit(Endstop* endstop);          // disables IRQ


void endstop_setup_gpio(Endstop* endstop);      // setups gpio for endstop

uint8_t endstop_clicked(Endstop* endstop);      // returns if endstop is clicked or not

#endif // ENDSTOP_H
