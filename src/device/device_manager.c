#include "device/device_manager.h"

#include "null.h"
#include "data_assistant.h"

#include "device/low_voltage/stepper/config/stepper_connection.h"
#include "device/low_voltage/stepper/partial/stepper_setup.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_callback.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

#include "device/low_voltage/endstop/endstop.h"
#include "device/low_voltage/endstop/config/endstop_connection.h"
#include "device/low_voltage/endstop/partial/endstop_setup.h"
#include "device/low_voltage/endstop/partial/endstop_operation.h"

#include "device/high_voltage/pomp/config/pomp_connection.h"
#include "device/high_voltage/th_phase_motor/config/th_phase_motor_connection.h"

Stepper steppers[STEPPERS_COUNT] = {0};
Endstop endstops[ENDSTOPS_COUNT] = {0};

Stepper *W_STEPPER = NULL;
Stepper *X_STEPPER = NULL;
Stepper *Y_STEPPER = NULL;
Stepper *Z_STEPPER = NULL;

HVD POMP;
HVD TH_PHASE_MOTOR;

void device_manager_init()
{
    // create stepper with configs
    stepper_init(&steppers[0], CIRCULAR, (uint8_t *)"w", W_MASTER_TIMER, W_SLAVE_TIMER, W_ALTERNATE_FUNCTION, W_CHANNEL, W_ITR, W_IRQ,
                 W_ENABLE_PORT, W_ENABLE_PIN, W_STEP_PORT, W_STEP_PIN, W_DIR_PORT, W_DIR_PIN);

    stepper_init(&steppers[1], LINEAR, (uint8_t *)"x", X_MASTER_TIMER, X_SLAVE_TIMER, X_ALTERNATE_FUNCTION, X_CHANNEL, X_ITR, X_IRQ,
                 X_ENABLE_PORT, X_ENABLE_PIN, X_STEP_PORT, X_STEP_PIN, X_DIR_PORT, X_DIR_PIN);

    stepper_init(&steppers[2], LINEAR, (uint8_t *)"y", Y_MASTER_TIMER, Y_SLAVE_TIMER, Y_ALTERNATE_FUNCTION, Y_CHANNEL, Y_ITR, Y_IRQ,
                 Y_ENABLE_PORT, Y_ENABLE_PIN, Y_STEP_PORT, Y_STEP_PIN, Y_DIR_PORT, Y_DIR_PIN);

    stepper_init(&steppers[3], LINEAR, (uint8_t *)"z", Z_MASTER_TIMER, Z_SLAVE_TIMER, Z_ALTERNATE_FUNCTION, Z_CHANNEL, Z_ITR, Z_IRQ,
                 Z_ENABLE_PORT, Z_ENABLE_PIN, Z_STEP_PORT, Z_STEP_PIN, Z_DIR_PORT, Z_DIR_PIN);

    // create endstops with configs
    endstop_init(&endstops[0], (uint8_t *)"xl", XL_PORT, XL_PIN, XL_IRQ);
    endstop_init(&endstops[1], (uint8_t *)"xr", XR_PORT, XR_PIN, XR_IRQ);

    endstop_init(&endstops[2], (uint8_t *)"yl", YL_PORT, YL_PIN, YL_IRQ);
    endstop_init(&endstops[3], (uint8_t *)"yr", YR_PORT, YR_PIN, YR_IRQ);

    endstop_init(&endstops[4], (uint8_t *)"zl", ZL_PORT, ZL_PIN, ZL_IRQ);
    endstop_init(&endstops[5], (uint8_t *)"zr", ZR_PORT, ZR_PIN, ZR_IRQ);

    // create additional pointers to steppers
    W_STEPPER = &steppers[0];
    X_STEPPER = &steppers[1];
    Y_STEPPER = &steppers[2];
    Z_STEPPER = &steppers[3];

    // assign endstops to steppers
    stepper_assignEndstops(X_STEPPER, &endstops[0], &endstops[1]);
    stepper_assignEndstops(Y_STEPPER, &endstops[2], &endstops[3]);
    stepper_assignEndstops(Z_STEPPER, &endstops[4], &endstops[5]);

    // create pomp and th-phase motor
    hvd_init(&POMP, POMP_PORT, POMP_PIN);
    hvd_init(&TH_PHASE_MOTOR, TH_PHASE_MOTOR_PORT, TH_PHASE_MOTOR_PIN);
}

void device_manager_deinit()
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
        stepper_deinit(&steppers[i]);

    for (i = 0; i < ENDSTOPS_COUNT; i++)
        endstop_deinit(&endstops[i]);

    hvd_deinit(&POMP);
    hvd_deinit(&TH_PHASE_MOTOR);
}

Stepper *device_manager_getStepper(uint8_t *name)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stringEqual(stepper_getName(stepper), name))
            return stepper;
    }

    return NULL;
}

Stepper *device_manager_findParentStepper(Endstop *endstop)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stepper->minEndstop == endstop || stepper->maxEndstop == endstop)
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
void device_manager_manageEndstops()
{
    uint8_t i = 0;

    for (i = 0; i < ENDSTOPS_COUNT; i++)
    {
        Endstop *endstop = &endstops[i];

        if (endstop->debounce.CLICKED_FLAG)
            endstop_debounce(endstop);
    }
}

void device_manager_manageSteppers()
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stepper->movement.FINISHED_FLAG)
            stepperFinishedCallback(stepper);
        else
            stepper_watchdog(stepper);
    }
}

void device_manager_manageDevices()
{
    device_manager_manageEndstops();
    device_manager_manageSteppers();
}

void device_manager_getAllDevicesStates(uint8_t *s)
{
    uint8_t *states = EMPTY;

    uint8_t i = 0;

    for (i = 0; i < STEPPERS_COUNT; i++)
        states = charAppend(states, stepper_getState(&steppers[i]));

    for (i = 0; i < ENDSTOPS_COUNT; i++)
        states = charAppend(states, endstop_isClicked(&endstops[i]));

    states = strAppend(states, hvd_getState(&POMP));
    states = strAppend(states, hvd_getState(&TH_PHASE_MOTOR));

    *s = states;
}
