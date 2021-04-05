#include "device/endstop/partial/endstop_callback.h"

#include "command/partial/data_assistant.h"

#include "device/stepper/stepper.h"
#include "device/stepper/partial/stepper_callback.h"
#include "device/stepper/partial/stepper_intervention.h"
#include "device/stepper/partial/stepper_operation.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"
#include "device/stepper/partial/stepper_helper.h"

#include "process.h"

enum
{
    HOME_FINISHED = 1,
    HOME_CONTINUE = 0,
};

uint8_t endstop_homeCallback(Stepper *stepper)
{
    if (getHomeStep(stepper) == FAST_BACKWARD) // first step of home
    {
        stepper_home(stepper, SLOW_FORWARD);
        return HOME_CONTINUE;
    }

    return HOME_FINISHED;
}

// [CALLED FROM MAIN LOOP]
void endstopClickedCallback(Endstop *endstop)
{
    Stepper *stepper = device_manager_findParentStepper(endstop);

    // process is currenty running && forward moving && clicked MAX X endstop
    if (PROCESS_FORWARD && stringEqual(endstop->name, (uint8_t *)"XR")) // cannot compares strings like here
        process_reverse();

    // check if parent stepper is currently running to avoid random signal or press by hand
    else if (getState(stepper) == HOMING || getState(stepper) == MOVING)
    {
        if (getState(stepper) == HOMING)
        {
            // first condition is to be sure the endstop will not stop stepper if it homing and outgoing
            if (getHomeStep(stepper) == SLOW_FORWARD || endstop_homeCallback(stepper) == HOME_CONTINUE)
                return;
        }

        stepper_stop(stepper);

        uart_send(cmd_builder_buildFin(getIndex(stepper))); // this is info mainly for end HOME operation, but mby can happen in normal move if overtaken
    }
}