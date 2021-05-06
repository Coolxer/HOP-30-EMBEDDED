#include "device/endstop/partial/endstop_operation.h"

#include "config.h"

#include "device/endstop/partial/endstop_callback.h"

uint8_t endstop_isClicked(Endstop *endstop)
{
    return HAL_GPIO_ReadPin((GPIO_TypeDef *)endstop->port, endstop->pin);
}

void endstop_debounce(Endstop *endstop)
{
    if (endstop->DEBOUNCING_FLAG == RESET)
    {
        endstop->time = HAL_GetTick();
        endstop->DEBOUNCING_FLAG = SET;
    }
    else
    {
        if ((HAL_GetTick() - endstop->time) >= ENDSTOP_DEBOUNCE_TIME) // time interval counted up (finished)
        {
            endstop->CLICKED_FLAG = endstop->DEBOUNCING_FLAG = RESET;

            if (endstop_isClicked(endstop)) // check if after DEBOUNCE_TIME endstop still be clicked
                endstopClickedCallback(endstop);
        }
    }
}