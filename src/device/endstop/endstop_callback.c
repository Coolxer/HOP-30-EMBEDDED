#include "device/endstop/partial/endstop_callback.h"

#include "command/partial/data_assistant.h"

#include "device/stepper/stepper.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_callback.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_operation.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

#include "process.h"

enum
{
    HOME_FINISHED = 1,
    HOME_CONTINUE = 0,
};

uint8_t endstop_homeCallback(Stepper *stepper)
{
    if (stepper_isHomeStep(stepper, FAST_BACKWARD)) // first step of home
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
    else if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING))
    {
        if (!stepper_isHomeStep(stepper, SLOW_FORWARD)) // be sure the endstop will not stop stepper if it homing and outgoing
            stepper_stopTimers(stepper);

        if (stepper_isState(stepper, HOMING))
        {
            if (endstop_homeCallback(stepper) == HOME_CONTINUE)
                return;
        }

        stepper_resetSpeed(stepper);
        stepper_setState(stepper, ON);

        uart_send(cmd_builder_buildFin(stepper->info.index)); // this is info mainly for end HOME operation, but mby can happen in normal move if overtaken
    }
}