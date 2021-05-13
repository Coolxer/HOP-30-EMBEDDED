#include "multiple_operations.h"

#include "null.h"

#include "command/partial/data_assistant.h"
#include "command/cmd_builder.h"

uint8_t getCommandSteppersAmount(uint8_t *value)
{
    if (stringEqual(value, VAL.PROCESS))
        return 2;
    else if (stringEqual(value, VAL.ALL))
        return 4;
    else if (device_manager_getStepper(value))
        return 1;

    return 0;
}

uint8_t *validateSteppers(uint8_t *idx, uint8_t *key, uint8_t *value, uint8_t *steppersAmount, uint8_t *stepperIndex)
{

    if (validate_key(KEY.STEPPER, key) == ERR.ERROR)
        return cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);

    *steppersAmount = getCommandSteppersAmount(value);

    if (*steppersAmount == 0)
        return cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
    else if (*steppersAmount == 1)
        *stepperIndex = device_manager_getStepperIndex(value);

    return EMPTY;
}

uint8_t *operate(uint8_t *idx, uint8_t *value1, uint8_t *value2, uint8_t steppersAmount, uint8_t stepperIndex,
                 uint8_t (*validate)(Stepper *, uint8_t *, uint8_t *), void (*operate)(Stepper *, uint8_t *, uint8_t *))
{
    // setup for loops
    uint8_t i = 0;
    uint8_t end = steppersAmount;
    uint8_t err = 0;

    if (stepperIndex != 9)
    {
        i = stepperIndex;
        end = stepperIndex;
    }

    // validate stepper(s)
    for (i; i <= end; i++)
    {
        if (validate(&steppers[i], value1, value2))
        {
            err = 1;
            break;
        }
    }

    // operate on stepper(s)
    if (!err)
    {
        for (i; i <= end; i++)
            operate(&steppers[i], value1, value2);

        return cmd_builder_buildFin(idx);
    }

    return cmd_builder_buildErr(idx, ERR.OPERATION_NOT_ALLOWED);
}
