#include "endstop/partial/endstop_operation.h"

uint8_t endstop_isClicked(Endstop *endstop)
{
    return HAL_GPIO_ReadPin((GPIO_TypeDef *)endstop->port, endstop->pin);
}