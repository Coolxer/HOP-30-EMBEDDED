#include "counter.h"

#include "config/clock.h"

TIM_HandleTypeDef counterTimer;

void counter_init()
{
    counterTimer.Instance = TIM14;
    counterTimer.Init.Prescaler = (CLOCK_FREQUENCY / 1000000) - 1;
    counterTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    counterTimer.Init.Period = 65535;
    counterTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&counterTimer);

    //__HAL_TIM_SET_AUTORELOAD(&counterTimer, 0);
    HAL_TIM_Base_Start(&counterTimer);
}

void counter_deinit()
{
    HAL_TIM_Base_Stop(&counterTimer);
}

void counter_count(uint16_t micros)
{
#ifndef UNIT_TEST
    __HAL_TIM_SET_COUNTER(&counterTimer, 0); // reset counter
    while (__HAL_TIM_GET_COUNTER(&counterTimer) < micros)
        ;
#endif
}
