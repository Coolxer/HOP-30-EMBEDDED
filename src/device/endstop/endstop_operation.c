#include "device/endstop/partial/endstop_operation.h"

uint8_t endstop_isClicked(Endstop *endstop)
{
    return !HAL_GPIO_ReadPin((GPIO_TypeDef *)endstop->port, endstop->pin);
}

void endstop_debounce(Endstop *endstop)
{
    uint8_t state = endstop_isClicked(endstop);

    if (state != endstop->lastState)
    {
        
    }
}