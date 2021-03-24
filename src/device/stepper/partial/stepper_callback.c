#include "device/stepper/partial/stepper_callback.h"

#include "device/stepper/enum/state.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_operation.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

//  [CALLED FROM MAIN LOOP]
void stepperFinishedCallback(Stepper *stepper)
{
    if (stepper_isHomeStep(stepper, SLOW_FORWARD))
    {
        stepper_stopTimers(stepper);
        stepper->movement.FINISHED_FLAG = RESET;

        stepper_home(stepper, PRECISE_BACKWARD);
    }
    else if (stepper_manageSlaveTimer(stepper) == NOT_RELOADED)
    {
        stepper_stopTimers(stepper);
        stepper->movement.FINISHED_FLAG = RESET;

        stepper_reset(stepper);

        stepper_updateStates(stepper, ON);
        uart_send(cmd_builder_buildFin(stepper->info.index));
    }
}
