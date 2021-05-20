#include "device/low_voltage/endstop/partial/endstop_operation.h"

#include "config.h"

#include "device/low_voltage/endstop/partial/endstop_callback.h"

uint8_t endstop_isClicked(Endstop *endstop)
{
    return HAL_GPIO_ReadPin((GPIO_TypeDef *)endstop->hardware.port, endstop->hardware.pin);
}

void endstop_debounce(Endstop *endstop)
{
    if (endstop->debounce.DEBOUNCING_FLAG == RESET)
    {
        endstop->debounce.time = HAL_GetTick();
        endstop->debounce.DEBOUNCING_FLAG = SET;
        endstop->debounce.counter = 1;
    }

    if ((HAL_GetTick() - endstop->debounce.time) >= ENDSTOP_DEBOUNCE_TIME) // time interval counted up (finished)
    {
        if (endstop_isClicked(endstop)) // check if after DEBOUNCE_TIME endstop still be clicked
            endstop->debounce.counter++;
        else
        {
            endstop->debounce.CLICKED_FLAG = endstop->debounce.DEBOUNCING_FLAG = RESET;
            endstop->debounce.counter = 0;
            return;
        }

        if (endstop->debounce.counter >= ENDSTOP_DEBOUNCE_AMOUNT)
            endstopClickedCallback(endstop);
    }
}