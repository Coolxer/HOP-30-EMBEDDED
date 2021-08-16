#include "device/low_voltage/stepper/partial/stepper_callback.h"

#include <string.h>

#include "device/low_voltage/stepper/partial/stepper_peripheral.h"
#include "device/low_voltage/stepper/partial/stepper_intervention.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

#include "command/response/response_builder.h"
#include "command/cmd_manager.h"

//  [CALLED FROM MAIN LOOP]
void stepperFinishedCallback(Stepper *stepper)
{
    stepper->movement.FINISHED_FLAG = RESET;

    // stepper counted up, try to reload registers, if not it is really end
    if (stepper_reload(stepper))
        return;

    stepper_stop(stepper);

    justRegisteredCallbackResponseIndex = (justRegisteredCallbackResponseIndex < MAX_BUFFER_RESPONSES) ? justRegisteredCallbackResponseIndex + 1 : MAX_BUFFER_REQUESTS + 1;

    strcpy((void *)RESPONSES[justRegisteredCallbackResponseIndex], response_builder_buildFin(stepper_getIndex(stepper)));
}
