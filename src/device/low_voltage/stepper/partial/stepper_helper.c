#include "device/low_voltage/stepper/partial/stepper_helper.h"

/* INFO SECTION */

enum AxisType stepper_getAxisType(Stepper *stepper)
{
    return stepper->info.axisType;
}

uint8_t stepper_getName(Stepper *stepper)
{
    return stepper->info.name;
}

uint8_t *stepper_getIndex(Stepper *stepper)
{
    return stepper->info.index;
}

void stepper_setIndex(Stepper *stepper, uint8_t *index)
{
    stepper->info.index = index;
}

/* END OF INFO SECTION */

/* ACCELERATION SECTION */

float stepper_getCurrentAcceleration(Stepper *stepper)
{
    return stepper->acceleration.current;
}

void stepper_setCurrentAcceleration(Stepper *stepper, float acceleration)
{
    stepper->acceleration.current = acceleration;
}

uint32_t stepper_getStepsNeededToAccelerate(Stepper *stepper)
{
    return stepper->acceleration.stepsNeededToAccelerate;
}

void stepper_setStepsNeededToAccelerate(Stepper *stepper, uint32_t steps)
{
    stepper->acceleration.stepsNeededToAccelerate = steps;
}

/* END OF ACCELERATION SECTION */

/* MOVEMENT SECTION */

uint16_t stepper_getRest(Stepper *stepper)
{
    return stepper->movement.rest;
}

void stepper_setRest(Stepper *stepper, uint16_t rest)
{
    stepper->movement.rest = rest;
}

uint32_t stepper_getUnloadedSteps(Stepper *stepper)
{
    return stepper->movement.unloadedSteps;
}

void stepper_setUnloadedSteps(Stepper *stepper, uint32_t steps)
{
    stepper->movement.unloadedSteps = steps;
}

enum MoveType stepper_getMoveType(Stepper *stepper)
{
    return stepper->movement.type;
}

void stepper_setMoveType(Stepper *stepper, enum MoveType type)
{
    stepper->movement.type = type;
}

/* END OF MOVEMENT SECTION */

/* SPEED SECTION */

float stepper_getCurrentSpeed(Stepper *stepper)
{
    return stepper->speed.current;
}

void stepper_setCurrentSpeed(Stepper *stepper, float speed)
{
    stepper->speed.current = speed;

    if (stepper_getSpeedType(stepper) == DYNAMIC)
        stepper_setSpeedState(stepper, RAISING);
}

float stepper_getTargetSpeed(Stepper *stepper)
{
    return stepper->speed.target;
}

void stepper_setTargetSpeed(Stepper *stepper, float speed)
{
    stepper->speed.target = speed;
}

uint32_t stepper_getLastTimeUpdate(Stepper *stepper)
{
    return stepper->speed.lastTimeUpdate;
}

void stepper_updateLastTime(Stepper *stepper)
{
    stepper->speed.lastTimeUpdate = HAL_GetTick();
}

enum SpeedType stepper_getSpeedType(Stepper *stepper)
{
    return stepper->speed.type;
}

void stepper_setSpeedType(Stepper *stepper, enum SpeedType type)
{
    stepper->speed.type = type;
}

enum SpeedState stepper_getSpeedState(Stepper *stepper)
{
    return stepper->speed.state;
}

void stepper_setSpeedState(Stepper *stepper, enum SpeedState state)
{
    stepper->speed.state = state;
}

/* END OF SPEED SECTION */

/* HARDWARE SECTION*/

TIM_HandleTypeDef *stepper_getSlaveTimer(Stepper *stepper)
{
    return &stepper->hardware.slaveTimer;
}

uint32_t stepper_getTarget(Stepper *stepper)
{
    return stepper->hardware.slaveTimer.Instance->ARR;
}

uint32_t stepper_getProgress(Stepper *stepper)
{
    return stepper->hardware.slaveTimer.Instance->CNT;
}

/* END OF HARDWARE SECTION */

enum State stepper_getState(Stepper *stepper)
{
    return stepper->info.state;
}

void stepper_setState(Stepper *stepper, enum State state)
{
    stepper->info.state = state;
}

uint8_t stepper_getDirection(Stepper *stepper)
{
    return stepper->movement.direction;
}

uint8_t stepper_isDirectionInverted(Stepper *stepper)
{
    return stepper->info.invertedDirection;
}
