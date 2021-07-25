#include "command/request/request_validator.h"

#include "null.h"
#include "data_assistant.h"
#include "validator.h"
#include "communication/config/communication.h"

#include "command/response/response_builder.h"
#include "command/cmd_manager.h"

uint8_t *request_checkMinLength(uint8_t *request)
{
    if (stringLength(request) < MIN_TRUNC_REQUEST_SIZE)
        return response_builder_buildErr(ZERO_INDEX, ERR.INVALID_REQUEST_LENGTH);

    return EMPTY;
}

uint8_t *request_checkGeneralThings(uint8_t ***args, uint8_t records)
{
    if (records == 0) // check if no records detected
        return response_builder_buildErr(ZERO_INDEX, ERR.NO_PARAMS);
    else if (records == 1) // check if there is only one record
        return response_builder_buildErr(ZERO_INDEX, ERR.ONE_PARAM_ONLY);
    else if (records > 5) // check if there is more than 5 records
        return response_builder_buildErr(ZERO_INDEX, ERR.TO_MANY_PARAMS);

    if (args != NULL && validate_key(KEY.INDEX, args[0][0]) == ERR.ERROR) // check if there is no "idx" key
        return response_builder_buildErr(ZERO_INDEX, ERR.NO_INDEX_KEY);

    uint8_t *index = args[0][1];

    if (!containsOnlyDigits(index))
        return response_builder_buildErr(ZERO_INDEX, ERR.INVALID_INDEX_VALUE);

    if (args != NULL && validate_key(KEY.OPERATION, args[1][0]) == ERR.ERROR) // check if there is no "opt" key
        return response_builder_buildErr(index, ERR.NO_OPERATION_KEY);

    return EMPTY;
}

uint8_t *request_validateRequestKeys(uint8_t ***args, uint8_t *index, uint8_t *requiredKeys[], uint8_t requiredKeysAmount)
{
    uint8_t i = 0;

    for (i = 0; i < requiredKeysAmount; i++)
    {
        if (validate_key(requiredKeys[i], args[i][0]) == ERR.ERROR)
            return response_builder_buildErr(index, cmd_manager_getErrorByKey(requiredKeys[i], KEY_ERROR));
    }

    return EMPTY;
}
