#include "device/stepper/structure/stepper_movement.h"

Movement stepper_movement_init()
{
    Movement movement = {0};
    movement.rest = 0;

    Way_params way = {0};
    way.laps = 0;
    way.arr = 0;

    movement.way = way;

    return movement;
}