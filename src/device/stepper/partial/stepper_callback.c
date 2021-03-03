#include "device/stepper/partial/stepper_callback.h"

#include "enum/type.h"

#include "device/device_manager.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_operation.h"

uint8_t stepper_homeProcedureOnEndstopClicked()
{
    if (stepper_isHomeStep(int_stepper, FAST)) // first step of home
    {
        stepper_setHomeStep(int_stepper, BACKWARD);
        stepper_home(int_stepper);

        return HOME_CONTINUE;
    }
    else                                        // current step of home is PRECISE
        stepper_setHomeStep(int_stepper, FAST); // means that there is finish home operation

    return HOME_FINISHED;
}

void stepper_homeProcedureOnStepperFinished()
{
    // when current state of home is BACKWARD
    stepper_stopTimers(int_stepper);

    stepper_setHomeStep(int_stepper, PRECISE);
    stepper_home(int_stepper);
}
