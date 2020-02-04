//#ifdef STSTM32
#include "device_manager.h"

#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "stepper.h"
#include "endstop.h"

void device_manager_init()
{
    steppers[0] = stepper_init("x", TIM3, TIM_CHANNEL_1, TIM4, TIM_TS_ITR2, TIM4_IRQn, GPIO_AF2_TIM3, GPIOA, 15, 6, 10, 7, 9, 8);

    //devices[0] = (Device*)stepper_init(DIVIDER_NAME, DIVIDER_TIMER, DIVIDER_ALTERNATE, DIVIDER_CHANNEL, DIVIDER_PORT, DIVIDER_DIR, DIVIDER_STEP, DIVIDER_ENABLE, DIVIDER_M1, DIVIDER_M2, DIVIDER_M3);
    //devices[1] = (Device*)stepper_init(TABLE_NAME, TABLE_TIMER, TABLE_ALTERNATE, TABLE_CHANNEL, TABLE_PORT, TABLE_DIR, TABLE_STEP, TABLE_ENABLE, TABLE_M1, TABLE_M2, TABLE_M3);

    //devices[2] = (Device*)endstop_init(devices[0], DIVIDER_MIN_ENDSTOP_NAME, DIVIDER_MIN_ENDSTOP_PORT, DIVIDER_MIN_ENDSTOP_EXT, DIVIDER_MIN_ENDSTOP_PIN);

    stepper = NULL;
    endstop = NULL;

    stepper = (Stepper *)malloc(sizeof(Stepper)); // reserves memory for operting stepper
    endstop = (Endstop *)malloc(sizeof(Endstop)); // reserves memory for operating endstop
}

uint8_t device_manager_set_current(uint8_t *name)
{
    uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(strcmp(steppers[i]->name, name) == 0)
        {
            stepper = steppers[i];
            return 1;
        }
    }

    return 0;
}

void device_manager_deinit()
{
    /*
    device_manager_set_current("x");
    stepper_deinit();
    device_manager_set_current("w");
    stepper_deinit();
    device_manager_set_current("e1");
    endstop_deinit();

    */
   __HAL_RCC_TIM3_CLK_DISABLE();
   __HAL_RCC_TIM4_CLK_DISABLE();
   //__HAL_RCC_TIM3_CLK_DISABLE();
   //__HAL_RCC_TIM3_CLK_DISABLE();
}

uint8_t device_manager_get_current()
{
    if(stepper)
        return 1;

    return 0;
}

void device_manager_release_device()
{
    stepper = NULL;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint8_t i;
    //uint8_t counter = 0; // need it because, there can 2 timers finished its jobs same time and cannot decrease launched count, beacuse need to check all, and after loop
    //                     // can decrease it, shouldn't break the loop too 

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(htim->Instance == steppers[i]->slave_timer.Instance)
        {
            HAL_TIM_PWM_Stop(&steppers[i]->master_timer, steppers[i]->channel); // stop PWM (moving) on assigned stepper
		    HAL_TIM_Base_Stop_IT(&steppers[i]->slave_timer);
        }
    }
}

//#endif // STSTM32