#include "command/request/request_validator.h"

#include "null.h"
#include "data/assistant.h"
#include "data/validator.h"

#include "command/cmd_manager.h"

uint8_t request_checkGeneralThings(uint8_t ***args, uint8_t records)
{
    if (records == 0) // check if no records detected
        return ERR.NO_PARAMS;
    else if (records == 1) // check if there is only one record
        return ERR.ONE_PARAM_ONLY;
    else if (records > 5) // check if there is more than 5 records
        return ERR.TO_MANY_PARAMS;

    if (args != NULL && validate_key(KEY.INDEX, args[0][0]) == ERR.ERROR) // check if there is "idx" key
        return ERR.NO_INDEX_KEY;

    uint8_t *index = args[0][1];

    if (!containsOnlyDigits(index))
        return ERR.INVALID_INDEX_VALUE;

    if (args != NULL && validate_key(KEY.OPERATION, args[1][0]) == ERR.ERROR) // check if there is "opt" key
        return ERR.NO_OPERATION_KEY;

    return ERR.NO_ERROR;
}

uint8_t request_validateRequestKeys(uint8_t ***args, uint8_t *requiredKeys[], uint8_t requiredKeysAmount)
{
    uint8_t i = 0;

    for (i = 0; i < requiredKeysAmount; i++)
    {
        if (validate_key(requiredKeys[i], args[i][0]) == ERR.ERROR)
            return cmd_manager_getErrorByKey(requiredKeys[i], KEY_ERROR);
    }

    return ERR.NO_ERROR;
}
