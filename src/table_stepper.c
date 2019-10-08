//#ifdef STSTM32
#include "table_stepper.h"

struct Stepper *create_table_stepper()
{
    stepper_init(&table_stepper, "s2", TABLE_TIMER, TABLE_PORT, TABLE_DIR, TABLE_STEP, TABLE_ENABLE, TABLE_M1, TABLE_M2, TABLE_M3, TABLE_MIN_ENDSTOP, TABLE_MAX_ENDSTOP); // set for "s2" stepper

    __HAL_RCC_TIM4_CLK_ENABLE(); // init TIM4, which service table motor

    return &table_stepper;
}

void release_table_stepper()
{
    __HAL_RCC_TIM4_CLK_DISABLE();  // deinit TIM3, which service divider motor
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == table_stepper.timer.Instance)
    {
        uint8_t state = table_stepper.state;
        
        if(!state)
        {
            HAL_GPIO_WritePin(table_stepper.port, table_stepper.step_pin, GPIO_PIN_SET);
            state = 1;
        }
        else
        {
            HAL_GPIO_WritePin(table_stepper.port, table_stepper.step_pin, GPIO_PIN_SET);
            state = 0;
        }
    }
}

//#endif // STSTM32