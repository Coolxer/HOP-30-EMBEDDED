#include "device/device_callback.h"

#include "device/device_manager.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_helper.h"

// callback fires up, when endstop is clicked [INTERRUPT SERVICE]
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t i = 0;

    for (i = 0; i < ENDSTOPS_COUNT; i++) // go through all endstops to check which fire the callback
    {
        if (GPIO_Pin == endstops[i].pin) // check if concret endstop fired interrupt
        {
            endstops[i].CLICKED_FLAG = SET;
            break;
        }
    }
}

// callback fires up, when slave timer (counter of PWM pulses amount) reaches target (finish stepper movement) [INTERRUPT SERVICE]
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++) // go through all steppers to check which fired the callback
    {
        if (htim->Instance == stepper_getSlaveTimer(&steppers[i])->Instance) // check which timer send callback
        {
            steppers[i].movement.FINISHED_FLAG = SET;
            break;
        }
    }
}
