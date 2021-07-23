#include "command/request/request_manager.h"

#include <string.h>
#include <stdlib.h>

#include "null.h"
#include "data_assistant.h"

#include "command/partial/err.h"
#include "command/partial/res.h"
#include "command/partial/type.h"

#include "command/request/request_validator.h"
#include "command/request/request_parser.h"
#include "command/request/request_operator.h"
#include "command/response/response_builder.h"

#include "communication/connector.h"

#include "device/device_manager.h"

uint8_t *request_process()
{
    uint8_t *feedback = EMPTY;

    // STEP 1: TRUNCATE REQUEST
    uint8_t *request = request_truncate(dma.requestBuffer);

    // STEP 2: VALIDATE REQUEST COMMAND LENGTH
    if (!stringLength(feedback = request_checkMinLength(request)))
        return feedback;

    // STEP 3: EXPLODE FOR PAIRS KEY:VALUE
    uint8_t ***args = request_explode(request);

    // STEP 4: GENERAL VALIDATION (RECORDS, INDEX, OPERATION CHECKS)
    if (!stringLength(feedback = request_checkGeneralThings(args, records)))
        return feedback;

    // STEP 5: GET INDEX AND OPERATION TYPE
    uint8_t *index = args[0][1];
    uint8_t *operation = args[1][1];

    // STEP 6: SCHRINK DATA TO LEAVE ONLY NEEDED DATA

    // decrease number of rows by 2 (remove index and operation)
    records = (uint8_t)(records - 2);

    // move the array 2 place forward (removes 2 first rows with idx and opt)
    memmove(args, args + 2, records * sizeof(uint8_t *));

    // STEP 7: CHECK IF OPERATION TYPE IS FINE AND PREPARE DATA FOR NEXT STEPS DEPEND ON OPERATION
    if (!stringLength(feedback = request_operate(index, operation)))
        return feedback;

    // STEP 8: VALIDATE REQUEST KEYS
    if (requiredRequestKeysAmount > 0)
    {
        if (!stringLength(feedback = request_validateRequestKeys(args, index, requiredRequestKeys, requiredRequestKeysAmount)))
            return feedback;
    }

    // STEP 9: VALIDATE REQUEST VALUES AND ENVIRONMENT STATES
    Stepper *st = NULL;

    if (validateRequestFunction != NULL)
    {
        if (stepper)
        {
            st = device_manager_getStepper(args[0][1]);

            if (!st)
                return response_builder_buildErr(index, ERR.INVALID_STEPPER_VALUE);

            uint8_t code = validateRequestFunction(st, args[1][1], args[2][1]);

            if (code != ERR.NO_ERROR)
                return response_builder_buildErr(index, code);
        }
        else
        {
            uint8_t code = validateRequestFunction(NULL, args[1][1], EMPTY);

            if (code != ERR.NO_ERROR)
                return response_builder_buildErr(index, code);
        }
    }

    // STEP 10: EXECUTE COMMAND
    if (stepper)
        executeRequestFunction(st, args[1][1], args[2][1]);
    else if (hvd)
        executeRequestFunction(hvd, args[1][1], args[2][1]);
    else
        executeRequestFunction(NULL, args[1][1], args[2][1]);

    if (requestType == INSTANT)
        return response_builder_buildPas(index);
    else
        return response_builder_buildFin(index);

    return EMPTY;
}