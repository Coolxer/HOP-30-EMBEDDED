//#ifdef STSTM32
#include "device_manager.h"

#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "stepper.h"
#include "endstop.h"

Stepper* current;

void device_manager_init()
{
    current = NULL;

    steppers[0] = *stepper_init("x", TIM3, TIM_CHANNEL_1, TIM4, TIM_TS_ITR2, TIM4_IRQn, GPIO_AF2_TIM3, GPIOA, 15, 6, 10, 7, 9, 8);

    //devices[0] = (Device*)stepper_init(DIVIDER_NAME, DIVIDER_TIMER, DIVIDER_ALTERNATE, DIVIDER_CHANNEL, DIVIDER_PORT, DIVIDER_DIR, DIVIDER_STEP, DIVIDER_ENABLE, DIVIDER_M1, DIVIDER_M2, DIVIDER_M3);
    //devices[1] = (Device*)stepper_init(TABLE_NAME, TABLE_TIMER, TABLE_ALTERNATE, TABLE_CHANNEL, TABLE_PORT, TABLE_DIR, TABLE_STEP, TABLE_ENABLE, TABLE_M1, TABLE_M2, TABLE_M3);

    //devices[2] = (Device*)endstop_init(devices[0], DIVIDER_MIN_ENDSTOP_NAME, DIVIDER_MIN_ENDSTOP_PORT, DIVIDER_MIN_ENDSTOP_EXT, DIVIDER_MIN_ENDSTOP_PIN);

    //stepper = (Stepper *)calloc(sizeof(Stepper)); // reserves memory for operting stepper
    //endstop = (Endstop *)calloc(sizeof(Endstop)); // reserves memory for operating 
}

void device_manager_deinit()
{
    uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
        stepper_deinit(&steppers[i]);

    for(i = 0; i < ENDSTOPS_COUNT; i++)
        endstop_deinit(&endstops[i]);
}

Stepper* device_manager_set_current(uint8_t *name)
{
    uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(strcmp(steppers[i].name, name) == 0)
            return &steppers[i];
    }

    return NULL;
}

void EXTI4_IRQHandler(void)
{
    uint8_t i;

    for(int i = 0; i < ENDSTOPS_COUNT; i++)
        HAL_GPIO_EXTI_IRQHandler(endstops[i].pin); // runs external interrupt on endstop pin
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t i;

    for(int i = 0; i < ENDSTOPS_COUNT; i++)
    {
        if(GPIO_Pin == endstops[i].pin)
        {
            HAL_TIM_PWM_Stop(&endstop->parent_stepper->master_timer, endstop->parent_stepper->channel); // stop PWM (moving) on assigned stepper
            HAL_TIM_Base_Stop_IT(&endstop->parent_stepper->slave_timer);
        }
    }   
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(htim->Instance == steppers[i].slave_timer.Instance)
        {
            HAL_TIM_PWM_Stop(&steppers[i].master_timer, steppers[i].channel); // stop PWM (moving) on assigned stepper
		    HAL_TIM_Base_Stop_IT(&steppers[i].slave_timer);
        }
    }
}

//#endif // STSTM32