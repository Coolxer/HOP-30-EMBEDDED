#include "device/stepper/structure/stepper_movement.h"

Movement stepper_movement_init()
{
    Movement movement = {0};

    movement.rest = 0;
    movement.target = 0;

    movement.FINISHED_FLAG = 0;

    return movement;
}
