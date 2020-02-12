//#ifdef STSTM32
#include "device_manager.h"

#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "stepper.h"
#include "endstop.h"

#include "uart.h"
#include "data_assistant.h"

#define STEPPERS_COUNT 4                                                        
#define ENDSTOPS_COUNT 6                                                        

Stepper steppers[STEPPERS_COUNT];                 
Endstop endstops[ENDSTOPS_COUNT];

void device_manager_init()
{
    stepper_init(&steppers[0], X_NAME, X_PORT, X_MASTER_TIMER, X_SLAVE_TIMER, X_ALTERNATE_FUNCTION, X_CHANNEL, X_ITR, X_IRQ, X_STEP, X_DIR, X_ENABLE, X_M1, X_M2, X_M3);
    stepper_init(&steppers[1], Y_NAME, Y_PORT, Y_MASTER_TIMER, Y_SLAVE_TIMER, Y_ALTERNATE_FUNCTION, Y_CHANNEL, Y_ITR, Y_IRQ, Y_STEP, Y_DIR, Y_ENABLE, Y_M1, Y_M2, Y_M3);
    stepper_init(&steppers[2], Z_NAME, Z_PORT, Z_MASTER_TIMER, Z_SLAVE_TIMER, Z_ALTERNATE_FUNCTION, Z_CHANNEL, Z_ITR, Z_IRQ, Z_STEP, Z_DIR, Z_ENABLE, Z_M1, Z_M2, Z_M3);
    stepper_init(&steppers[3], W_NAME, W_PORT, W_MASTER_TIMER, W_SLAVE_TIMER, W_ALTERNATE_FUNCTION, W_CHANNEL, W_ITR, W_IRQ, W_STEP, W_DIR, W_ENABLE, W_M1, W_M2, W_M3);

    endstop_init(&endstops[0], XL_NAME, &steppers[0], XL_PORT, XL_PIN, XL_IRQ);
    endstop_init(&endstops[1], XR_NAME, &steppers[0], XR_PORT, XR_PIN, XR_IRQ);

    endstop_init(&endstops[2], YL_NAME, &steppers[1], YL_PORT, YL_PIN, YL_IRQ);
    endstop_init(&endstops[3], YR_NAME, &steppers[1], YR_PORT, YR_PIN, YR_IRQ);

    endstop_init(&endstops[3], ZL_NAME, &steppers[2], ZL_PORT, ZL_PIN, ZL_IRQ);
    endstop_init(&endstops[4], ZR_NAME, &steppers[2], ZR_PORT, ZR_PIN, ZR_IRQ);

    PROCESS_FORWARD = 0;
}

void device_manager_deinit()
{
    uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
        stepper_deinit(&steppers[i]);

    for(i = 0; i < ENDSTOPS_COUNT; i++)
        endstop_deinit(&endstops[i]);
}

Stepper *device_manager_getStepper(uint8_t *name)
{
    uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(strcmp((void *)steppers[i].name, (void *)name) == 0)
            return &steppers[i];
    }

    return NULL;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == XR_PIN && PROCESS_FORWARD)
    {
        stepper_changeDirection(&steppers[0]);
        stepper_changeDirection(&steppers[3]);

        PROCESS_FORWARD = 0;
        return;
    }

    uint8_t i;

    for(i = 0; i < ENDSTOPS_COUNT; i++)
    {
        if(GPIO_Pin == endstops[i].pin)
        {
            if(endstop->parentStepper->state != HOMING && endstop->parentStepper->state != MOVING)
                return;

            HAL_TIM_PWM_Stop(&endstop->parentStepper->masterTimer, endstop->parentStepper->channel); // stop PWM (moving) on assigned stepper

            uint32_t cnt = 0;

            if(endstop->parentStepper->state == MOVING)
                 cnt = endstop->parentStepper->slaveTimer.Instance->CNT;
 
            HAL_TIM_Base_Stop_IT(&endstop->parentStepper->slaveTimer); // this isnt necessary when home operation, but probably not destroying antything

            uint8_t* feedback = str_append(endstop->name, (uint8_t*)"_ENDSTOP_HIT");

            if(cnt)
            {
                feedback = str_append(feedback, (uint8_t*)"_STEPS=");

                uint8_t *str = (uint8_t*)"";
                sprintf((void*)str, (void*)cnt);

                feedback = str_append(feedback, str);
            }

            endstop->parentStepper->lastState = endstop->parentStepper->state = ON;

            uart_send(feedback); // this is info mainly for end HOME operation, but mby can happen in normal move if overtaken
        }
    }   
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(htim->Instance == steppers[i].slaveTimer.Instance)
        {
            HAL_TIM_PWM_Stop(&steppers[i].masterTimer, steppers[i].channel); // stop PWM (moving) on assigned stepper
		    HAL_TIM_Base_Stop_IT(&steppers[i].slaveTimer);

            stepper_reset(&steppers[i]);

            steppers[i].lastState = steppers[i].state = ON;

            uint8_t *feedback = str_append((uint8_t*)"_SUCCESS_", (uint8_t*)steppers[i].name);

            uart_send(feedback);

            //free(feedback);
        }
    }
}

//#endif // STSTM32