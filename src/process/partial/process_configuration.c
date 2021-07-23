#include "process/partial/process_configuration.h"

#include "device/device_manager.h"
#include "device/low_voltage/stepper./partial/stepper_configuration.h"

void process_configure(uint8_t direction)
{
    stepper_setDirection(X_STEPPER, RIGHT);
    stepper_setDirection(W_STEPPER, direction);
}
