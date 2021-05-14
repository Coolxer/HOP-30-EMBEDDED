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

uint8_t getErrorByKey(uint8_t *key)
{
    if (stringEqual(KEY.OPERATION, key))
        return ERR.NO_OPERATION_KEY;
    else if (stringEqual(KEY.INDEX, key))
        return ERR.NO_INDEX_KEY;
    else if (stringEqual(KEY.STEPPER, key))
        return ERR.NO_STEPPER_KEY;
    else if (stringEqual(KEY.SPEED, key))
        return ERR.NO_SPEED_KEY;
    else if (stringEqual(KEY.ACCELERATION, key))
        return ERR.NO_ACCELERATION_KEY;
    else if (stringEqual(KEY.WAY, key))
        return ERR.NO_WAY_KEY;
    else if (stringEqual(KEY.STATE, key))
        return ERR.NO_STATE_KEY;
    else if (stringEqual(KEY.DIRECTION, key))
        return ERR.NO_DIRECTION_KEY;

    return 255;
}

/*
   void func(uint8_t **arr, uint8_t count)
{
    printf("%s", arr[1]);
}

int main()
{
    uint8_t *buff[4] = {"Hello function" , "How are you?" , "Catch some strings"};

    func(buff, 4);

    return 0;
}

*/

uint8_t *prepare(uint8_t *idx, uint8_t ***args, uint8_t **requiredKeys, uint8_t requiredKeysAmount,
                 uint8_t (*validate)(Stepper *, uint8_t *, uint8_t *), void (*operate)(Stepper *, uint8_t *, uint8_t *))
{
    uint8_t steppersAmount = 0;
    uint8_t stepperIndex = 9;

    uint8_t *feedback = EMPTY;

    uint8_t i = 0;

    for (i = 0; i < requiredKeysAmount; i++)
    {
        if (validate_key(requiredKeys[i], args[i][0]) == ERR.ERROR)
            return cmd_builder_buildErr(idx, getErrorByKey(requiredKeys[i]));
    }
}
