#include "stepper/partial/stepper_validator.h"

#include <string.h>

uint8_t set_speed_validator(Stepper *stepper, uint8_t *speed)
{
    uint8_t i = 0;
    uint8_t len = strlen((void *)speed);

    // mask [000.00]

    // empty (0) or too long (> 6)
    if (len == 0 || len > 6)
        return 0;

    else if (len == 1)
    {
        // ![1-9]
        if (!(speed[0] >= 49 && speed[0] <= 57))
            return 0;
    }

    else if (len == 2)
    {
        // ! ([1-9] and [0-9])
        if (!((speed[0] >= 49 && speed[0] <= 57) && (speed[1] >= 48 && speed[1] <= 57)))
            return 0;
    }

    else
    {
        // 0  ...
        if (speed[0] == '0')
        {
            // 0 !.
            if (speed[1] != '.')
                return 0;

            // 0 . and only two places after dot for digits (to fit 0.01 precision)
            // if len > 4 that means there is two much places after dot
            if (len > 4)
                return 0;

            uint8_t zeros = 0;

            for (i = 2; i < len; i++)
            {
                // ![0-9]
                if (!(speed[i] >= 48 && speed[i] <= 57))
                    return 0;

                if (speed[i] == '0')
                    zeros++;
            }

            // 0. and only zeros after dot, means nothing
            if ((len == 3 && zeros == 1) || zeros == 2)
                return 0;
        }
        else // !0 ...
        {
            uint8_t dot = 0;
            uint8_t digitsAfterDot = 0;

            for (i = 0; i < len; i++)
            {
                if (!((speed[i] >= 48 && speed[i] <= 57) || speed[i] == '.'))
                    return 0;

                // check if there is dot
                if (speed[i] == '.')
                {
                    // dot. cannot be first and last character
                    if (i == 0 || i == len - 1)
                        return 0;

                    // if there is first dot its ok
                    if (!dot)
                        dot = 1;
                    else // if there is second dot., there is error
                        return 0;
                }
                // if dot. exists
                else if (dot)
                {
                    // can register max 2 digits after dot.
                    if (digitsAfterDot < 2)
                        digitsAfterDot++;
                    else
                        return 0;
                }
            }

            // if dot. was detected, there must be at least one digit after
            if (dot && !digitsAfterDot)
                return 0;
        }
    }

    return 1;
}

uint8_t switch_validator(Stepper *stepper)
{
    if (stepper->state == HOMING || stepper->state == MOVING) // cannot switch motor if stepper is homing or moving
        return 0;

    return 1;
}

uint8_t home_validator(Stepper *stepper)
{
    if (((stepper->state == HOMING || stepper->state == MOVING) && stepper->homeStep == stepper->lastHomeStep) || stepper->state == PAUSED) // cannot home if motor is homing or moving right now or also paused
        return 0;

    return 1;
}

uint8_t move_validator(Stepper *stepper, uint8_t *way)
{
    uint8_t i = 1;
    uint8_t len = strlen((void *)way);

    if (stepper->state == HOMING || stepper->state == MOVING || stepper->state == PAUSED) // cannot move if motor is homing or moving or is paused right now
        return 9;

    // mask [-000.00]

    // empty (0) or too long (> 7)
    if (len == 0 || len > 7)
        return 0;

    else if (len == 1)
    {
        // ![1-9]
        if (!(way[0] >= 49 && way[0] <= 57))
            return 0;
    }

    else if (len == 2)
    {
        // ! (- and [1-9])
        if (!(way[0] == '-' && (way[1] >= 49 && way[1] <= 57))
            // ! ([1-9] and [0-9])
            && !((way[0] >= 49 && way[0] <= 57) && (way[1] >= 48 && way[1] <= 57)))
            return 0;
    }

    else if (len == 3)
    {
        // ! ([1-9] and [0-9] and [0-9])
        if (!((way[0] >= 49 && way[0] <= 57) && (way[1] >= 48 && way[1] <= 57) && (way[2] >= 48 && way[2] <= 57))
            // ! (- and [1-9] and [0-9])
            && !(way[0] == '-' && (way[1] >= 49 && way[1] <= 57) && (way[2] >= 48 && way[2] <= 57))
            // ! (0 and . and [0-9])
            && !(way[0] == '0' && way[1] == '.' && (way[2] >= 48 && way[2] <= 57))

        )
            return 0;
    }

    else
    {
        // 0  ...
        if (way[0] == '0')
        {
            // 0 !.
            if (way[1] != '.')
                return 0;

            // 0 . and only two places after dot for digits (to fit 0.01 precision)
            // if len > 4 that means there is two much places after dot.
            if (len > 4)
                return 0;

            uint8_t zeros = 0;

            for (i = 2; i < len; i++)
            {
                // ![0-9]
                if (!(way[i] >= 48 && way[i] <= 57))
                    return 0;

                if (way[i] == '0')
                    zeros++;
            }

            // 0. and only zeros after dot, means nothing
            if ((len == 3 && zeros == 1) || zeros == 2)
                return 0;
        }
        else // !0 ...
        {
            uint8_t dot = 0;
            uint8_t digitsAfterDot = 0;

            // ! (- or [1-9])
            if (!(way[0] == '-' || (way[0] >= 49 && way[0] <= 57)))
                return 0;

            for (i = 1; i < len; i++)
            {
                if (!(way[i] == '.' || (way[i] >= 48 && way[i] <= 57)))
                    return 0;

                // check if there is dot
                if (way[i] == '.')
                {
                    // dot. cannot be first and last character
                    if (i == 0 || i == len - 1)
                        return 0;

                    // if there is first dot its ok
                    if (!dot)
                        dot = 1;
                    else // if there is second dot., there is error
                        return 0;
                }
                // if dot. exists
                else if (dot)
                {
                    // can register max 2 digits after dot.
                    if (digitsAfterDot < 2)
                        digitsAfterDot++;
                    else
                        return 0;
                }
            }

            // if dot. was detected, there must be at least one digit after
            if (dot && !digitsAfterDot)
                return 0;
        }
    }

    return 1;
}

uint8_t pause_validator(Stepper *stepper)
{
    if ((stepper->state != HOMING && stepper->state != MOVING) || stepper->state == PAUSED) // cannot pause if stepper is not homing, not moving or if it is already paused
        return 0;

    return 1;
}

uint8_t resume_validator(Stepper *stepper)
{
    if (stepper->state != PAUSED) // cannot resume stepper if it's not paused
        return 0;

    return 1;
}

uint8_t stop_validator(Stepper *stepper)
{
    if (stepper->state != HOMING && stepper->state != MOVING && stepper->state != PAUSED) // cannot stop motor if its not homing, moving or not paused
        return 0;

    return 1;
}
