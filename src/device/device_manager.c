#include "device/device_manager.h"

#include "null.h"
#include "command/partial/data_assistant.h"

#include "device/stepper/config/stepper_config.h"
#include "device/stepper/partial/stepper_setup.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_callback.h"

#include "device/endstop/endstop.h"
#include "device/endstop/config/endstop_connection.h"
#include "device/endstop/partial/endstop_setup.h"
#include "device/endstop/partial/endstop_operation.h"

Stepper steppers[STEPPERS_COUNT] = {0};
Endstop endstops[ENDSTOPS_COUNT] = {0};

Stepper *X_STEPPER = NULL;
Stepper *Y_STEPPER = NULL;
Stepper *Z_STEPPER = NULL;
Stepper *W_STEPPER = NULL;

void device_manager_init()
{
    stepper_config(); // prepares config data

    stepper_init(&steppers[0], LINEAR, X_NAME, X_HARDWARE, X_SPEED, X_ACCELERATION);
    stepper_init(&steppers[1], LINEAR, Y_NAME, Y_HARDWARE, Y_SPEED, Y_ACCELERATION);
    stepper_init(&steppers[2], LINEAR, Z_NAME, Z_HARDWARE, Z_SPEED, Z_ACCELERATION);
    stepper_init(&steppers[3], CIRCULAR, W_NAME, W_HARDWARE, W_SPEED, W_ACCELERATION);

    endstop_init(&endstops[0], XL_NAME, XL_PORT, XL_PIN, XL_IRQ);
    endstop_init(&endstops[1], XR_NAME, XR_PORT, XR_PIN, XR_IRQ);

    endstop_init(&endstops[2], YL_NAME, YL_PORT, YL_PIN, YL_IRQ);
    endstop_init(&endstops[3], YR_NAME, YR_PORT, YR_PIN, YR_IRQ);

    endstop_init(&endstops[4], ZL_NAME, ZL_PORT, ZL_PIN, ZL_IRQ);
    endstop_init(&endstops[5], ZR_NAME, ZR_PORT, ZR_PIN, ZR_IRQ);

    stepper_assignEndstops(&steppers[0], &endstops[0], &endstops[1]);
    stepper_assignEndstops(&steppers[1], &endstops[2], &endstops[3]);
    stepper_assignEndstops(&steppers[2], &endstops[4], &endstops[5]);

    X_STEPPER = &steppers[0];
    Y_STEPPER = &steppers[1];
    Z_STEPPER = &steppers[2];
    W_STEPPER = &steppers[3];
}

void device_manager_deinit()
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
        stepper_deinit(&steppers[i]);

    for (i = 0; i < ENDSTOPS_COUNT; i++)
        endstop_deinit(&endstops[i]);
}

Stepper *device_manager_getStepper(uint8_t *name)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stringEqual(stepper->info.name, name))
            return stepper;
    }

    return NULL;
}

Endstop *device_manager_getEndstop(uint8_t *name)
{
    uint8_t i = 0;

    for (i = 0; i < ENDSTOPS_COUNT; i++)
    {
        Endstop *endstop = &endstops[i];

        if (stringEqual(endstop->name, name))
            return endstop;
    }

    return NULL;
}

Stepper *device_manager_findParentStepper(Endstop *endstop)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stepper->minEndstop == endstop || steppers->maxEndstop == endstop)
            return stepper;
    }

    return NULL;
}

void manageEndstops()
{
    uint8_t i = 0;

    for (i = 0; i < ENDSTOPS_COUNT; i++)
    {
        Endstop *endstop = &endstops[i];

        if (endstop->CLICKED_FLAG)
            endstop_debounce(endstop);
    }
}

void manageSteppers()
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stepper->instance.FINISHED_FLAG)
            stepperFinishedCallback(stepper);

        if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING))
        {
            if (stepper->acceleration.current > 0)
                stepper_accelerate(stepper);
        }
    }
}

void manageDevices()
{
    manageEndstops();
    manageSteppers();
}
