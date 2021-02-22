#include "validator.h"

#include <string.h>
#include "command/partial/err.h"

uint8_t validate_boolean(uint8_t *value)
{
    if (strcmp((void *)value, "0") == 0 || strcmp((void *)value, "1") == 0)
        return ERR.NO_ERROR;

    return ERR.ERROR;
}

uint8_t validate_float(uint8_t *value)
{
    uint8_t i = 0;
    uint8_t len = (uint8_t)strlen((void *)value);

    // mask [000.00]

    // empty (0) or too long (> 6)
    if (len == 0 || len > 6)
        return ERR.ERROR;

    else if (len == 1)
    {
        // ![1-9]
        if (!(value[0] >= 49 && value[0] <= 57))
            return ERR.ERROR;
    }

    else if (len == 2)
    {
        // ! ([1-9] and [0-9])
        if (!((value[0] >= 49 && value[0] <= 57) && (value[1] >= 48 && value[1] <= 57)))
            return ERR.ERROR;
    }

    else
    {
        // 0  ...
        if (value[0] == '0')
        {
            // 0 !.
            if (value[1] != '.')
                return ERR.ERROR;

            // 0 . and only two places after dot for digits (to fit 0.01 precision)
            // if len > 4 that means there is two much places after dot
            if (len > 4)
                return ERR.ERROR;

            uint8_t zeros = 0;

            for (i = 2; i < len; i++)
            {
                // ![0-9]
                if (!(value[i] >= 48 && value[i] <= 57))
                    return ERR.ERROR;

                if (value[i] == '0')
                    zeros++;
            }

            // 0. and only zeros after dot, means nothing
            if ((len == 3 && zeros == 1) || zeros == 2)
                return ERR.ERROR;
        }
        else // !0 ...
        {
            uint8_t dot = 0;
            uint8_t digitsAfterDot = 0;

            for (i = 0; i < len; i++)
            {
                if (!((value[i] >= 48 && value[i] <= 57) || value[i] == '.'))
                    return ERR.ERROR;

                // check if there is dot
                if (value[i] == '.')
                {
                    // dot. cannot be first and last character
                    if (i == 0 || i == len - 1)
                        return ERR.ERROR;

                    // if there is first dot its ok
                    if (!dot)
                        dot = 1;
                    else // if there is second dot., there is ERR
                        return ERR.ERROR;
                }
                // if dot. exists
                else if (dot)
                {
                    // can register max 2 digits after dot.
                    if (digitsAfterDot < 2)
                        digitsAfterDot++;
                    else
                        return ERR.ERROR;
                }
            }

            // if dot. was detected, there must be at least one digit after
            if (dot && !digitsAfterDot)
                return ERR.ERROR;
        }
    }

    return ERR.NO_ERROR;
}