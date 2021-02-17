#include "stepper/partial/stepper_validator.h"

#include <string.h>

uint8_t set_speed_validator(Stepper *stepper, uint8_t *speed)
{
    uint8_t len = strlen((void *)speed);
    uint8_t i;

    if (len == 0 || len > 3) // check if string is empty or too long
        return 0;
    else
    {
        if (speed[0] == '0') // check if string starts with 0
            return 0;
    }

    for (i = 0; i < len; i++)
    {
        if (speed[i] < 48 || speed[i] > 57) // check if string contains only numbers
            return 0;
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
    uint8_t len = strlen((void *)way);

    if (stepper->state == HOMING || stepper->state == MOVING || stepper->state == PAUSED) // cannot move if motor is homing or moving or is paused right now
        return 9;

    if (len == 0) // check if length of string is 0
        return 0;
    else if (len >= 1 && way[0] == '0') // check if length is more than 1 (OK), but not ok if it's starting with 0
        return 0;

    if ((way[0] < 48 || way[0] > 58) && way[0] != '-') // check if it's not number and not "-" (minus) sign
        return 0;

    uint8_t i;

    for (i = 1; i < len; i++)
    {
        if (way[i] < 48 || way[i] > 57) // check if string contains only numbers
            return 0;
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
