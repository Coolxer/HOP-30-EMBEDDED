#include "device/device_manager.h"

#include "null.h"
#include "command/partial/data_assistant.h"

#include "device/stepper/config/stepper_connection.h"
#include "device/stepper/config/stepper_speed_constraint.h"
#include "device/stepper/partial/stepper_setup.h"
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

Stepper *int_stepper = NULL; // stepper received in interrupt

void device_manager_init()
{
    stepper_init(&steppers[0], LINEAR, X_NAME, X_PORT, X_MASTER_TIMER, X_SLAVE_TIMER, X_ALTERNATE_FUNCTION, X_CHANNEL, X_ITR, X_IRQ, X_STEP, X_DIR, X_ENABLE, X_MIN_SPEED, X_MAX_SPEED);
    stepper_init(&steppers[1], LINEAR, Y_NAME, Y_PORT, Y_MASTER_TIMER, Y_SLAVE_TIMER, Y_ALTERNATE_FUNCTION, Y_CHANNEL, Y_ITR, Y_IRQ, Y_STEP, Y_DIR, Y_ENABLE, Y_MIN_SPEED, Y_MAX_SPEED);
    stepper_init(&steppers[2], LINEAR, Z_NAME, Z_PORT, Z_MASTER_TIMER, Z_SLAVE_TIMER, Z_ALTERNATE_FUNCTION, Z_CHANNEL, Z_ITR, Z_IRQ, Z_STEP, Z_DIR, Z_ENABLE, Z_MIN_SPEED, Z_MAX_SPEED);
    stepper_init(&steppers[3], CIRCULAR, W_NAME, W_PORT, W_MASTER_TIMER, W_SLAVE_TIMER, W_ALTERNATE_FUNCTION, W_CHANNEL, W_ITR, W_IRQ, W_STEP, W_DIR, W_ENABLE, W_MIN_SPEED, W_MAX_SPEED);

    endstop_init(&endstops[0], XL_NAME, XL_PORT, XL_PIN, XL_IRQ);
    endstop_init(&endstops[1], XR_NAME, XR_PORT, XR_PIN, XR_IRQ);

    endstop_init(&endstops[2], YL_NAME, YL_PORT, YL_PIN, YL_IRQ);
    endstop_init(&endstops[3], YR_NAME, YR_PORT, YR_PIN, YR_IRQ);

    endstop_init(&endstops[3], ZL_NAME, ZL_PORT, ZL_PIN, ZL_IRQ);
    endstop_init(&endstops[4], ZR_NAME, ZR_PORT, ZR_PIN, ZR_IRQ);

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
        if (stringEqual(steppers[i].info.name, name))
            return &steppers[i];
    }

    return NULL;
}

Endstop *device_manager_getEndstop(uint8_t *name)
{
    uint8_t i = 0;

    for (i = 0; i < ENDSTOPS_COUNT; i++)
    {
        if (stringEqual(endstops[i].name, name))
            return &endstops[i];
    }

    return NULL;
}

Stepper *device_manager_findParentStepper(Endstop *endstop)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
        if (steppers[i].minEndstop == endstop || steppers[i].maxEndstop == endstop)
            return &steppers[i];

    return NULL;
}

void manageSteppers()
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stepper->instance.FINISHED_FLAG)
            stepperFinishedCallback(stepper);
    }
}

void manageEndstops()
{
    uint8_t i = 0;

    for (i = 0; i < ENDSTOPS_COUNT; i++)
    {
        Endstop *endstop = &endstops[i];

        if (endstop->CLICKED_FLAG)
            endstop_debounce(&endstops[i]);
    }
}

void manageDevices()
{
    manageEndstops();
    manageSteppers();
}
