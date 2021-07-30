#include "device/low_voltage/stepper/partial/stepper_callback.h"

#include "device/low_voltage/stepper/partial/stepper_peripheral.h"
#include "device/low_voltage/stepper/partial/stepper_intervention.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

#include "command/response/response_builder.h"
#include "communication/connector.h"

//  [CALLED FROM MAIN LOOP]
void stepperFinishedCallback(Stepper *stepper)
{
    stepper->movement.FINISHED_FLAG = RESET;

    // stepper counted up, try to reload registers, if not it is really end
    if (stepper_reload(stepper))
        return;

    stepper_stop(stepper);

    connector_sendResponse(response_builder_buildFin(stepper_getIndex(stepper)));
}
