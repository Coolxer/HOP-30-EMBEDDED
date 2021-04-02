#include "device/stepper/partial/stepper_callback.h"

#include "device/stepper/enum/state.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_intervention.h"
#include "device/stepper/partial/stepper_operation.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

//  [CALLED FROM MAIN LOOP]
void stepperFinishedCallback(Stepper *stepper)
{
    // stepper counted up, try to reload registers, if not it is really end
    uint8_t reload = stepper_reload(stepper);

    if (!reload)
    {
        stepper_stop(stepper);
        stepper->movement.FINISHED_FLAG = RESET;

        // if the movoment was homing'outgoing, then continue move
        if (stepper_isHomeStep(stepper, SLOW_FORWARD))
            stepper_home(stepper, PRECISE_BACKWARD);

        else // if the movement was simple movement by user typing
            uart_send(cmd_builder_buildFin(stepper->info.index));
    }
}
