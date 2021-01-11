//#ifdef STSTM32
#include "device_manager.h"

#include <string.h>
#include <stdlib.h>

#include "cmd_builder.h"
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
    stepper_init(&steppers[0], X_NAME, X_PORT, X_MASTER_TIMER, X_SLAVE_TIMER, X_ALTERNATE_FUNCTION, X_CHANNEL, X_ITR, X_IRQ, X_STEP, X_DIR, X_ENABLE, X_MIN_SPEED, X_MAX_SPEED);
    stepper_init(&steppers[1], Y_NAME, Y_PORT, Y_MASTER_TIMER, Y_SLAVE_TIMER, Y_ALTERNATE_FUNCTION, Y_CHANNEL, Y_ITR, Y_IRQ, Y_STEP, Y_DIR, Y_ENABLE, Y_MIN_SPEED, Y_MAX_SPEED);
    stepper_init(&steppers[2], Z_NAME, Z_PORT, Z_MASTER_TIMER, Z_SLAVE_TIMER, Z_ALTERNATE_FUNCTION, Z_CHANNEL, Z_ITR, Z_IRQ, Z_STEP, Z_DIR, Z_ENABLE, Z_MIN_SPEED, Z_MAX_SPEED);
    stepper_init(&steppers[3], W_NAME, W_PORT, W_MASTER_TIMER, W_SLAVE_TIMER, W_ALTERNATE_FUNCTION, W_CHANNEL, W_ITR, W_IRQ, W_STEP, W_DIR, W_ENABLE, W_MIN_SPEED, W_MAX_SPEED);

    endstop_init(&endstops[0], XL_NAME, XL_PORT, XL_PIN, XL_IRQ);
    endstop_init(&endstops[1], XR_NAME, XR_PORT, XR_PIN, XR_IRQ);

    endstop_init(&endstops[2], YL_NAME, YL_PORT, YL_PIN, YL_IRQ);
    endstop_init(&endstops[3], YR_NAME, YR_PORT, YR_PIN, YR_IRQ);

    endstop_init(&endstops[3], ZL_NAME, ZL_PORT, ZL_PIN, ZL_IRQ);
    endstop_init(&endstops[4], ZR_NAME, ZR_PORT, ZR_PIN, ZR_IRQ);

    stepper_assignEndstops(&steppers[0], &endstops[0], &endstops[1]);
    stepper_assignEndstops(&steppers[1], &endstops[2], &endstops[3]);
    stepper_assignEndstops(&steppers[2], &endstops[4], &endstops[5]);

    PROCESS_FORWARD = 0; // set PROCESS_FORWARD (which mean the process forward moving is not in progress, so it's backward or process is not currently run)
}

void device_manager_deinit()
{
    uint8_t i;

    for (i = 0; i < STEPPERS_COUNT; i++)
        stepper_deinit(&steppers[i]);

    for (i = 0; i < ENDSTOPS_COUNT; i++)
        endstop_deinit(&endstops[i]);
}

Stepper *device_manager_getStepper(uint8_t *name)
{
    uint8_t i;

    for (i = 0; i < STEPPERS_COUNT; i++)
    {
        if (strcmp((void *)steppers[i].name, (void *)name) == 0)
            return &steppers[i];
    }

    return NULL;
}

Endstop *device_manager_getEndstop(uint8_t *name)
{
    uint8_t i;

    for (i = 0; i < ENDSTOPS_COUNT; i++)
    {
        if (strcmp((void *)endstops[i].name, (void *)name) == 0)
            return &endstops[i];
    }

    return NULL;
}

Stepper *device_manager_findParentStepper(Endstop *endstop)
{
    uint8_t i;

    for (i = 0; i < STEPPERS_COUNT; i++)
        if (steppers[i].minEndstop == endstop || steppers[i].maxEndstop == endstop)
            return &steppers[i];
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t i = 0; // for loop variable

    if (PROCESS_FORWARD && GPIO_Pin == XR_PIN) // if process forward moving is in progress, and hitted endstop is max of X axis
    {
        stepper_changeDirection(device_manager_getStepper((uint8_t *)"x"));
        stepper_changeDirection(device_manager_getStepper((uint8_t *)"w"));

        PROCESS_FORWARD = 0; // reset forward flag
        return;
    }

    for (i = 0; i < ENDSTOPS_COUNT; i++) // go through all endstops to check which fire the callback
    {
        if (GPIO_Pin == endstops[i].pin) // check if concret endstop fired interrupt
        {
            Endstop *endstop = &endstops[i]; // catch the current endstop

            Stepper *stepper = device_manager_findParentStepper(endstop);

            if (stepper->state != HOMING && stepper->state != MOVING) // if parent stepper is not HOMING or MOVING just break (prevent from random clicked)
                break;                                                // for example if endstop was clicked by hand

            HAL_TIM_PWM_Stop(&stepper->masterTimer, stepper->channel); // stop PWM (moving) on assigned stepper

            if (stepper->state == MOVING)                   // if the current parent stepper operation is MOVING stop the slave timer too
                HAL_TIM_Base_Stop_IT(&stepper->slaveTimer); // this isnt necessary when home operation, but probably not destroying anything

            stepper_reset(stepper); // reset stepper motor after finished his work

            stepper->state = ON; // reset state of parent motor

            uart_send(cmd_builder_buildFin(stepper->index, (uint8_t *)"2")); // this is info mainly for end HOME operation, but mby can happen in normal move if overtaken
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    uint8_t i;

    for (i = 0; i < STEPPERS_COUNT; i++) // go through all steppers to check which fired the callback
    {
        if (htim->Instance == steppers[i].slaveTimer.Instance) // check which timer send callback
        {
            stepper_stopTimers(&steppers[i]); // stop timers of correct stepper

            steppers[i].lastState = steppers[i].state = ON; // reset state of motor

            uart_send(cmd_builder_buildFin(steppers[i].index, (uint8_t *)"2")); // send feedback
        }
    }
}

//#endif // STSTM32