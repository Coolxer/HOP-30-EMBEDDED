//#ifdef STSTM32
#include "device_manager.h"

#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "stepper.h"
#include "endstop.h"

Stepper steppers[STEPPERS_COUNT];                 
Endstop endstops[ENDSTOPS_COUNT];

void device_manager_init()
{
    stepper_init(&steppers[0], X_NAME, X_PORT, X_MASTER_TIMER, X_SLAVE_TIMER, X_ALTERNATE_FUNCTION, X_CHANNEL, X_ITR, X_IRQ, X_STEP, X_DIR, X_ENABLE, X_M1, X_M2, X_M3);
    stepper_init(&steppers[1], Y_NAME, Y_PORT, Y_MASTER_TIMER, Y_SLAVE_TIMER, Y_ALTERNATE_FUNCTION, Y_CHANNEL, Y_ITR, Y_IRQ, Y_STEP, Y_DIR, Y_ENABLE, Y_M1, Y_M2, Y_M3);
    stepper_init(&steppers[2], Z_NAME, Z_PORT, Z_MASTER_TIMER, Z_SLAVE_TIMER, Z_ALTERNATE_FUNCTION, Z_CHANNEL, Z_ITR, Z_IRQ, Z_STEP, Z_DIR, Z_ENABLE, Z_M1, Z_M2, Z_M3);
    stepper_init(&steppers[3], W_NAME, W_PORT, W_MASTER_TIMER, W_SLAVE_TIMER, W_ALTERNATE_FUNCTION, W_CHANNEL, W_ITR, W_IRQ, W_STEP, W_DIR, W_ENABLE, W_M1, W_M2, W_M3);
}

void device_manager_deinit()
{
    uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
        stepper_deinit(&steppers[i]);

    for(i = 0; i < ENDSTOPS_COUNT; i++)
        endstop_deinit(&endstops[i]);
}

Stepper* device_manager_get_stepper(uint8_t *name)
{
    uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(strcmp(steppers[i].name, name) == 0)
            return &steppers[i];
    }

    return NULL;
}

/******************* ENDSTOPS INTERRUPTS HANDLERS *****************************/

void EXTI4_IRQHandler(void)
{
    uint8_t i;

    for(int i = 0; i < ENDSTOPS_COUNT; i++)
        HAL_GPIO_EXTI_IRQHandler(endstops[i].pin); // runs external interrupt on endstop pin
}

/******************** ENDSTOP INRERRUPT PROCEDURE *****************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t i;

    for(int i = 0; i < ENDSTOPS_COUNT; i++)
    {
        if(GPIO_Pin == endstops[i].pin)
        {
            HAL_TIM_PWM_Stop(&endstop->parent_stepper->masterTimer, endstop->parent_stepper->channel); // stop PWM (moving) on assigned stepper
            HAL_TIM_Base_Stop_IT(&endstop->parent_stepper->slaveTimer);
        }
    }   
}

/******************* STEPPERS INTERRUPTS HANDLERS *****************************/

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&steppers[0].slaveTimer);
}

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&steppers[1].slaveTimer);
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&steppers[2].slaveTimer);
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&steppers[3].slaveTimer);
}

/**************** STEPPER SLAVE TIMER INTERRUPT PROCEDURE  ********************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(htim->Instance == steppers[i].slaveTimer.Instance)
        {
            HAL_TIM_PWM_Stop(&steppers[i].masterTimer, steppers[i].channel); // stop PWM (moving) on assigned stepper
		    HAL_TIM_Base_Stop_IT(&steppers[i].slaveTimer);
        }
    }
}

//#endif // STSTM32