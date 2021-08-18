#include "command/request/request_manager.h"

#include <string.h>
#include <stdlib.h>

#include "null.h"
#include "data/assistant.h"

#include "command/partial/err.h"
#include "command/partial/res.h"

#include "command/request/structure/type.h"
#include "command/request/request_validator.h"
#include "command/request/request_parser.h"
#include "command/request/request_operator.h"

#include "command/response/response_builder.h"

#include "device/device_manager.h"

uint8_t *request_process(uint8_t *request)
{
    // STEP 1: EXPLODE FOR PAIRS KEY:VALUE
    uint8_t records = 0;
    uint8_t ***args = request_explode(request, &records);

    // STEP 2: GENERAL VALIDATION (RECORDS, INDEX, OPERATION CHECKS)
    uint8_t code = request_checkGeneralThings(args, records);

    if (code != CORRECT)
        return response_builder_buildErr(ZERO_INDEX, code);

    // STEP 3: GET INDEX AND OPERATION TYPE
    uint8_t *index = args[0][1];
    uint8_t *operation = args[1][1];

    // STEP 4: SCHRINK DATA TO LEAVE ONLY NEEDED DATA
    // decrease number of rows by 2 (remove index and operation)
    records = (uint8_t)(records - 2);

    // move the array 2 place forward (removes 2 first rows with idx and opt)
    memmove(args, args + 2, records * sizeof(uint8_t *));

    // STEP 5: CHECK IF OPERATION TYPE IS FINE AND PREPARE DATA FOR NEXT STEPS DEPEND ON OPERATION
    Request req = request_operate(operation);

    if (req.type != LONG_TERM && req.type != INSTANT && req.type != ANSWER)
        return response_builder_buildErr(index, ERR.INCORRECT_OPERATION_VALUE);

    // STEP 6: VALIDATE REQUEST KEYS
    if (req.requiredKeysAmount > 0)
    {
        code = request_validateRequestKeys(args, req.requiredKeys, req.requiredKeysAmount);

        if (code != CORRECT)
            return response_builder_buildErr(index, code);
    }

    // STEP 7: VALIDATE REQUEST VALUES AND ENVIRONMENT STATES
    // STEP 8: EXECUTE COMMAND

    Stepper *stepper = NULL;

    if (req.stepper)
    {
        stepper = device_manager_getStepper(args[0][1]);

        if (!stepper)
            return response_builder_buildErr(index, ERR.INCORRECT_STEPPER_VALUE);

        switch (req.numberOfValues)
        {
        case 0:
            code = (req.validateFunction) ? req.validateFunction(stepper) : CORRECT;

            if (code == CORRECT)
                req.executeFunction(stepper);

            break;

        case 1:
            code = (req.validateFunction) ? req.validateFunction(stepper, args[1][1]) : CORRECT;

            if (code == CORRECT)
                req.executeFunction(stepper, args[1][1]);

            break;

        case 2:
            code = (req.validateFunction) ? req.validateFunction(stepper, args[1][1], args[2][1]) : CORRECT;

            if (code == CORRECT)
                req.executeFunction(stepper, args[1][1], args[2][1]);

            break;

        default:
            return response_builder_buildErr(index, 1);
        }
    }
    else if (req.hvd)
    {
        code = (req.validateFunction) ? req.validateFunction(req.hvd, args[1][1]) : CORRECT;

        if (code == CORRECT)
            req.executeFunction(req.hvd, args[1][1]);
    }
    else
    {
        switch (req.numberOfValues)
        {
        case 0:
            code = (req.validateFunction) ? req.validateFunction() : CORRECT;

            if (code == CORRECT)
                req.executeFunction();

            break;

        case 1:
            code = (req.validateFunction) ? req.validateFunction(args[1][1]) : CORRECT;

            if (code == CORRECT)
                req.executeFunction(args[1][1]);

            break;

        case 2:
            code = (req.validateFunction) ? req.validateFunction(args[1][1], args[2][1]) : CORRECT;

            if (code == CORRECT)
                req.executeFunction(args[1][1], args[2][1]);

            break;

        default:
            return response_builder_buildErr(index, 1);
        }
    }

    // check if there was an error, just send it
    if (code != CORRECT)
        return response_builder_buildErr(index, code);

    // GIVE POSITIVE FEEDBACK
    if (req.type == LONG_TERM)
    {
        if (stepper)
            stepper_setIndex(stepper, index);
        else
            stepper_setIndex(X_STEPPER, index); // for process

        return response_builder_buildPas(index);
    }
    else if (req.type == INSTANT)
        return response_builder_buildFin(index);
    else if (req.type == ANSWER)
        return response_builder_buildVal(index, devicesStates);

    return response_builder_buildErr(index, 1);
}