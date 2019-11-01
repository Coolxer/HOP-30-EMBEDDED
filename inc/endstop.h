#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "device.h"

#include "stepper.h"

typedef struct 
{
    Device device;                              // device instance
    Stepper *parent_stepper;                    // pointer to parent stepper to which the endstop will affect

    uint32_t port;                              // gpio port, where the pin is connected        
    uint16_t pin;                               // endstop pin

    uint8_t ext;                                // external interrupt name pointer

    uint8_t clicked;                            // endstop status
}Endstop;

Endstop *endstop;                               // endstop pointer, using to make operations on actual selected endstop

Endstop *endstop_init(Stepper *_stepper, uint8_t *_name, uint32_t _port, uint8_t _ext, uint16_t _pin); // endstop "constructor" function

void endstop_deinit();                          // frees memory reserved for endstop operationg pointer
void endstop_setup_gpio();                      // setups gpio for endstop

uint8_t endstop_clicked();                      // returns if endstop is clicked or not

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin); // external interrupt function

#endif // ENDSTOP_H
