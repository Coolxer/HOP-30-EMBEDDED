#include "device/low_voltage/stepper/structure/stepper_movement.h"

Movement stepper_movement_init(float stepsPerUnit, uint8_t invertedDirection)
{
    Movement movement = {0};

    movement.stepsPerUnit = stepsPerUnit;

    movement.rest = 0;
    movement.unloadedSteps = 0;

    movement.type = LIMITED;
    movement.FINISHED_FLAG = 0;

    movement.direction = 0;
    movement.invertedDirection = invertedDirection;

    return movement;
}