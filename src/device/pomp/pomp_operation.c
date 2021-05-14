#include "device/pomp/partial/pomp_operation.h"

void pomp_switch(Pomp *pomp, uint8_t *state, uint8_t *EMPTY1)
{
    uint8_t st = convertStrToBoolean(state);

    if (HAL_GPIO_ReadPin(pomp->port, pomp->pin) != st)
        HAL_GPIO_WritePin((GPIO_TypeDef *)pomp->port, pomp->pin, st);
}