//#ifdef STSTM32
#include "divider_stepper.h"

struct Stepper *create_divider_stepper()
{
    stepper_init(&divider_stepper, "s1", DIVIDER_TIMER, DIVIDER_PORT, DIVIDER_DIR, DIVIDER_STEP, DIVIDER_ENABLE, DIVIDER_M1, DIVIDER_M2, DIVIDER_M3, 0, 0); // set for "s1" stepper
    
    __HAL_RCC_TIM3_CLK_ENABLE(); // init TIM3, which service divider motor

    return &divider_stepper;
}

void release_divider_stepper()
{
    __HAL_RCC_TIM3_CLK_DISABLE(); // deinit TIM3, which service divider motor
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == divider_stepper.timer.Instance)
    {
        uint8_t state = divider_stepper.state;
        
        if(!state)
        {
            HAL_GPIO_WritePin(divider_stepper.port, divider_stepper.step_pin, GPIO_PIN_SET);
            state = 1;
        }
        else
        {
            HAL_GPIO_WritePin(divider_stepper.port, divider_stepper.step_pin, GPIO_PIN_SET);
            state = 0;
        }
    }
}

//#endif // STSTM32