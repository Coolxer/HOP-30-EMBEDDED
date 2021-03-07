#include "device/endstop/partial/endstop_callback.h"

#include "enum/type.h"
#include "flag.h"

#include "command/partial/data_assistant.h"

#include "device/stepper/stepper.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_callback.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

#include "process.h"

uint8_t stepper_homeOnEndstopClickedCallback(Stepper *stepper)
{
    if (stepper_isHomeStep(stepper, FAST)) // first step of home
    {
        stepper_home(stepper, BACKWARD);
        return HOME_CONTINUE;
    }

    return HOME_FINISHED;
}

// [CALLED FROM MAIN LOOP]
void endstopClickedCallback(Endstop *endstop)
{
    Stepper *stepper = device_manager_findParentStepper(endstop);

    // process is currenty running && forward moving && clicked MAX X endstop
    if (PROCESS_FORWARD && stringEqual(endstop->name, "XR")) // cannot compares strings like here
        process_reverse();

    // check if parent stepper is currently running to avoid random signal or press by hand
    else if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING))
    {
        stepper_stopTimers(stepper);

        if (stepper_isState(stepper, HOMING))
        {
            if (stepper_homeOnEndstopClickedCallback(stepper) == HOME_CONTINUE)
                return;
        }

        stepper_setState(stepper, ON);

        uart_send(cmd_builder_buildFin(stepper->info.index)); // this is info mainly for end HOME operation, but mby can happen in normal move if overtaken
    }
}