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

    PROCESS_FORWARD = 0; // set PROCESS_FORWARD (which mean the process forward moving is not in progress)
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
    uint8_t i = 0;
    uint8_t state = HAL_GPIO_ReadPin(GPIOC, GPIO_Pin); // read state of pin that fired interrupt

    if(PROCESS_FORWARD) // if process forward moving is in progress
    {
        if(GPIO_Pin == XR_PIN && state) // check if the endstop that was clicked was the XR and the state of interrupt is high 
        {                               // i gonna change direction of motors and reset PROCESS_FORWARD flag
            stepper_changeDirection(&steppers[0]);
            stepper_changeDirection(&steppers[3]);

            endstops[1].clicked = 1;

            PROCESS_FORWARD = 0;
            return;
        }
    }

    for(i = 0; i < ENDSTOPS_COUNT; i++)
    {
        if(GPIO_Pin == endstops[i].pin) // check if concret endstop fired interrupt
        {
            uint8_t cnt = 0;
            Endstop *endstop = &endstops[i];

            if(endstop->clicked == state) // check if the endstop has actually current interrupt state, just break it (security of multi calling)
                break;

            uart_send("A");

            endstop->clicked = state; // update endstop->clicked state

            if(!endstop->clicked || (endstop->parentStepper->state != HOMING && endstop->parentStepper->state != MOVING)) // check if endstop->clicked is false or the current operation of
                break;                                                                                                    // parent stepper is not HOMING or MOVING just break (prevent from random clicked) 
                                                                                                                          // for example if endstop was clicked by hand
            HAL_TIM_PWM_Stop(&endstop->parentStepper->masterTimer, endstop->parentStepper->channel); // stop PWM (moving) on assigned stepper

            /*
            if(endstop->parentStepper->state == MOVING)
            {
                cnt = endstop->parentStepper->slaveTimer.Instance->CNT;
                HAL_TIM_Base_Stop_IT(&endstop->parentStepper->slaveTimer); // this isnt necessary when home operation, but probably not destroying antything
            }
              */   
            uint8_t* feedback = str_append(endstop->name, (uint8_t*)"_ENDSTOP_HIT\n"); // send feedback with endstop name that fired the interrupt
            
            if(cnt) // check if cnt is greater than 0, means that the movement was MOVING not HOMING, and i want to send number of steps made
            {
                feedback = str_append(feedback, (uint8_t*)"_STEPS="); // append steps label to feedback

                uint8_t *str = (uint8_t*)""; 
                sprintf((void*)str, (void*)cnt); // transform cnt number to string

                feedback = str_append(feedback, str); // append number of steps made to feedback
            }

            stepper_reset(endstop->parentStepper); // reset stepper motor after finished his work

            endstop->parentStepper->state = endstop->parentStepper->state = ON; // reset state of parent motor

            uart_send(feedback); // this is info mainly for end HOME operation, but mby can happen in normal move if overtaken
        }
    }   
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint8_t i;

    for(i = 0; i < STEPPERS_COUNT; i++)
    {
        if(htim->Instance == steppers[i].slaveTimer.Instance) // check which timer send callback
        {
            stepper_stopTimers(&steppers[i]); // stop timers of correct stepper

            steppers[i].lastState = steppers[i].state = ON; // reset state of motor

            uint8_t *feedback = str_append((uint8_t*)"_SUCCESS_", (uint8_t*)steppers[i].name); // prepare feedback

            uart_send(feedback); // send feedback
        }
    }
}

//#endif // STSTM32