#include "device/endstop/partial/endstop_operation.h"

#include "device/endstop/partial/endstop_callback.h"

const uint8_t DEBOUNCE_TIME = 20; // in miliseconds

uint8_t endstop_isClicked(Endstop *endstop)
{
    return !HAL_GPIO_ReadPin((GPIO_TypeDef *)endstop->port, endstop->pin);
}

void endstop_debounce_init(Endstop *endstop)
{
    endstop->time = HAL_GetTick();
    endstop->state = endstop_isClicked(endstop);
    endstop->DEBOUNCING = SET;
}

void endstop_debounce(Endstop *endstop)
{
    if (!endstop->DEBOUNCING)
        endstop_debounce_init(endstop);
    else
    {
        if (HAL_GetTick() - endstop->time >= DEBOUNCE_TIME) // time interval count up
        {
            endstop->CLICKED_FLAG = endstop->DEBOUNCING = RESET;

            if (endstop_isClicked(endstop) == endstop->state) // if state after interval is the same as state on start, then do operation
                endstopClickedCallback(endstop);
        }
    }
}