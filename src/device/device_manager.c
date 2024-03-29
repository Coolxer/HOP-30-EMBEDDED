#include "device/device_manager.h"

#include <string.h>

#include "null.h"
#include "data/assistant.h"

#include "device/low_voltage/stepper/config/stepper_calculation.h"
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

Stepper steppers[STEPPERS_AMOUNT] = {0};
Endstop endstops[ENDSTOPS_AMOUNT] = {0};

Stepper *A_STEPPER = NULL;
Stepper *X_STEPPER = NULL;
Stepper *Y_STEPPER = NULL;
Stepper *Z_STEPPER = NULL;

HVD POMP;
HVD TH_PHASE_MOTOR;

uint8_t devicesStates[12] = {0};

void device_manager_init()
{
    // create stepper with configs
    stepper_init(&steppers[0], A_NAME, A_STEPS_PER_DEGREE, A_DIR_INV, A_MASTER_TIMER, A_SLAVE_TIMER, A_ALTERNATE_FUNCTION, A_CHANNEL, A_ITR, A_IRQ,
                 A_ENABLE_PORT, A_ENABLE_PIN, A_STEP_PORT, A_STEP_PIN, A_DIR_PORT, A_DIR_PIN);

    stepper_init(&steppers[1], X_NAME, X_STEPS_PER_MM, X_DIR_INV, X_MASTER_TIMER, X_SLAVE_TIMER, X_ALTERNATE_FUNCTION, X_CHANNEL, X_ITR, X_IRQ,
                 X_ENABLE_PORT, X_ENABLE_PIN, X_STEP_PORT, X_STEP_PIN, X_DIR_PORT, X_DIR_PIN);

    stepper_init(&steppers[2], Y_NAME, Y_STEPS_PER_MM, Y_DIR_INV, Y_MASTER_TIMER, Y_SLAVE_TIMER, Y_ALTERNATE_FUNCTION, Y_CHANNEL, Y_ITR, Y_IRQ,
                 Y_ENABLE_PORT, Y_ENABLE_PIN, Y_STEP_PORT, Y_STEP_PIN, Y_DIR_PORT, Y_DIR_PIN);

    stepper_init(&steppers[3], Z_NAME, Z_STEPS_PER_MM, Z_DIR_INV, Z_MASTER_TIMER, Z_SLAVE_TIMER, Z_ALTERNATE_FUNCTION, Z_CHANNEL, Z_ITR, Z_IRQ,
                 Z_ENABLE_PORT, Z_ENABLE_PIN, Z_STEP_PORT, Z_STEP_PIN, Z_DIR_PORT, Z_DIR_PIN);

    // create endstops with configs
    endstop_init(&endstops[0], (uint8_t *)"xl", XL_PORT, XL_PIN, XL_IRQ);
    endstop_init(&endstops[1], (uint8_t *)"xr", XR_PORT, XR_PIN, XR_IRQ);

    endstop_init(&endstops[2], (uint8_t *)"yl", YL_PORT, YL_PIN, YL_IRQ);
    endstop_init(&endstops[3], (uint8_t *)"yr", YR_PORT, YR_PIN, YR_IRQ);

    endstop_init(&endstops[4], (uint8_t *)"zl", ZL_PORT, ZL_PIN, ZL_IRQ);
    endstop_init(&endstops[5], (uint8_t *)"zr", ZR_PORT, ZR_PIN, ZR_IRQ);

    // create additional pointers to steppers
    A_STEPPER = &steppers[0];
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

    for (i = 0; i < STEPPERS_AMOUNT; i++)
        stepper_deinit(&steppers[i]);

    for (i = 0; i < ENDSTOPS_AMOUNT; i++)
        endstop_deinit(&endstops[i]);

    hvd_deinit(&POMP);
    hvd_deinit(&TH_PHASE_MOTOR);
}

Stepper *device_manager_getStepper(uint8_t *name)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_AMOUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stepper_getName(stepper) == name[0])
            return stepper;
    }

    return NULL;
}

Stepper *device_manager_findParentStepper(Endstop *endstop)
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_AMOUNT; i++)
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

    for (i = 0; i < ENDSTOPS_AMOUNT; i++)
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

    for (i = 0; i < ENDSTOPS_AMOUNT; i++)
    {
        Endstop *endstop = &endstops[i];

        if (endstop->debounce.CLICKED_FLAG)
            endstop_debounce(endstop);
    }
}

void device_manager_manageSteppers()
{
    uint8_t i = 0;

    for (i = 0; i < STEPPERS_AMOUNT; i++)
    {
        Stepper *stepper = &steppers[i];

        if (stepper->movement.FINISHED_FLAG)
            stepperFinishedCallback(stepper);
        else
            stepper_watchdog(stepper);
    }
}

void device_manager_process()
{
    device_manager_manageEndstops();
    device_manager_manageSteppers();
}

void device_manager_updateDevicesStatesMap()
{
    uint8_t i = 0;
    uint8_t index = 0;

    for (i = 0; i < STEPPERS_AMOUNT; i++)
    {
        devicesStates[index] = (uint8_t)stepper_getState(&steppers[i]);
        index++;
    }

    for (i = 0; i < ENDSTOPS_AMOUNT; i++)
    {
        devicesStates[index] = (uint8_t)endstop_isClicked(&endstops[i]);
        index++;
    }

    devicesStates[index] = (uint8_t)hvd_getState(&POMP);
    devicesStates[index + 1] = (uint8_t)hvd_getState(&TH_PHASE_MOTOR);
}
