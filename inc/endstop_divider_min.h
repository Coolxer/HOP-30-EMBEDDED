#ifndef ENDSTOP_DIVIDER_MIN_H
#define ENDSTOP_DIVIDER_MIN_H

#include "endstop.h"

struct Endstop endstop_divider_min;

struct Endstop *create_endstop_divider_min();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif // ENDSTOP_DIVIDER_MIN_H
