#include "device/device_callback.h"

#include "flag.h"
#include "enum/type.h"

#include "device/device_manager.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_callback.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_operation.h"

#include "device/endstop/config/endstop_connection.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

#include "process.h"

// [CALLED FROM MAIN LOOP]
void endstopClickedCallback()
{
    if (PROCESS_FORWARD && !int_stepper)
        process_reverse();
    else
    {
        stepper_stopTimers(int_stepper);

        if (stepper_isState(int_stepper, HOMING))
        {
            if (stepper_homeProcedureOnEndstopClicked() == HOME_CONTINUE)
            {
                ENDSTOP_CLICKED = 0;
                return;
            }
        }

        stepper_setState(int_stepper, ON);

        uart_send(cmd_builder_buildFin(int_stepper->info.index)); // this is info mainly for end HOME operation, but mby can happen in normal move if overtaken
    }

    ENDSTOP_CLICKED = 0;
}

//  [CALLED FROM MAIN LOOP]
void stepperFinishedCallback()
{
    if (stepper_isState(int_stepper, HOMING) && stepper_isHomeStep(int_stepper, BACKWARD))
        stepper_homeProcedureOnStepperFinished(int_stepper);
    else if (stepper_manageSlaveTimer(int_stepper) == NOT_RELOADED)
    {
        stepper_finishMoving(int_stepper);

        uart_send(cmd_builder_buildFin(int_stepper->info.index));
    }

    STEPPER_FINISHED = 0;
}

// callback fires up, when endstop is clicked [INTERRUPT SERVICE]
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t i = 0; // for loop variable

    // if process forward moving is in progress, and hitted endstop is max of X axis
    if (PROCESS_FORWARD && GPIO_Pin == XR_PIN)
    {
        int_stepper = NULL;
        ENDSTOP_CLICKED = 1;
        return;
    }

    for (i = 0; i < ENDSTOPS_COUNT; i++) // go through all endstops to check which fire the callback
    {
        if (GPIO_Pin == endstops[i].pin) // check if concret endstop fired interrupt
        {
            Stepper *stepper = device_manager_findParentStepper(&endstops[i]);

            // if parent stepper is not HOMING or MOVING just break (prevent from random clicked)
            if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING))
            {
                int_stepper = stepper;

                ENDSTOP_CLICKED = 1;
                break;
            }
        }
    }
}

// callback fires up, when slave timer (counter of PWM pulses amount) reaches target (finish stepper movement) [INTERRUPT SERVICE]
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++) // go through all steppers to check which fired the callback
    {
        if (htim->Instance == steppers[i].hardware.slaveTimer.Instance) // check which timer send callback
        {
            int_stepper = &steppers[i];
            STEPPER_FINISHED = 1;
            break;
        }
    }
}