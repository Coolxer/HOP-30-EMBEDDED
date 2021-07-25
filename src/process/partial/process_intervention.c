#include "process/partial/process_intervention.h"

#include "null.h"

#include "process/process.h"

#include "device/device_manager.h"
#include "device/low_voltage/stepper/partial/stepper_intervention.h"

void process_pause()
{
    stepper_pause(X_STEPPER);
    stepper_pause(W_STEPPER);

    hvd_switch(&POMP, OFF);
    hvd_switch(&TH_PHASE_MOTOR, OFF);

    PROCESS_PREVIOUS_STATE = PROCESS_STATE;
    PROCESS_STATE = HALTED;
}

void process_resume()
{
    stepper_resume(X_STEPPER);
    stepper_resume(W_STEPPER);

    hvd_switch(&POMP, ON);
    hvd_switch(&TH_PHASE_MOTOR, ON);

    PROCESS_STATE = PROCESS_PREVIOUS_STATE;
}

void process_stop()
{
    stepper_stop(X_STEPPER);
    stepper_stop(W_STEPPER);

    hvd_switch(&POMP, OFF);
    hvd_switch(&TH_PHASE_MOTOR, OFF);

    PROCESS_STATE = PROCESS_PREVIOUS_STATE = NONE;
}