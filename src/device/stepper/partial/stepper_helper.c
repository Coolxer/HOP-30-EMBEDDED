#include "device/stepper/partial/stepper_helper.h"

/* INFO SECTION */

enum AxisType getAxisType(Stepper *stepper)
{
    return stepper->info.axisType;
}

uint8_t *getName(Stepper *stepper)
{
    return stepper->info.name;
}

uint8_t *getIndex(Stepper *stepper)
{
    return stepper->info.index;
}

void setIndex(Stepper *stepper, uint8_t *index)
{
    stepper->info.index = index;
}

/* END OF INFO SECTION */

/* ACCELERATION SECTION */

float getCurrentAcceleration(Stepper *stepper)
{
    return stepper->acceleration.current;
}

void setCurrentAcceleration(Stepper *stepper, float acceleration)
{
    stepper->acceleration.current = acceleration;
}

uint32_t getStepsNeededToAccelerate(Stepper *stepper)
{
    return stepper->acceleration.stepsNeededToAccelerate;
}

void setStepsNeededToAccelerate(Stepper *stepper, uint32_t steps)
{
    stepper->acceleration.stepsNeededToAccelerate = steps;
}

/* END OF ACCELERATION SECTION */

/* MOVEMENT SECTION */

uint16_t getRest(Stepper *stepper)
{
    return stepper->movement.rest;
}

void setRest(Stepper *stepper, uint16_t rest)
{
    stepper->movement.rest = rest;
}

uint32_t getTarget(Stepper *stepper)
{
    return stepper->movement.target;
}

void setTarget(Stepper *stepper, uint32_t target)
{
    stepper->movement.target = target;
}

enum MoveType getMoveType(Stepper *stepper)
{
    return stepper->movement.type;
}

void setMoveType(Stepper *stepper, enum MoveType type)
{
    stepper->movement.type = type;
}

/* END OF MOVEMENT SECTION */

/* SPEED SECTION */

float getCurrentSpeed(Stepper *stepper)
{
    return stepper->speed.current;
}

void setCurrentSpeed(Stepper *stepper, float speed)
{
    stepper->speed.current = speed;
}

float getTargetSpeed(Stepper *stepper)
{
    return stepper->speed.target;
}

void setTargetSpeed(Stepper *stepper, float speed)
{
    stepper->speed.target = speed;
}

uint32_t getLastTimeUpdate(Stepper *stepper)
{
    return stepper->speed.lastTimeUpdate;
}

void updateLastTime(Stepper *stepper)
{
    stepper->speed.lastTimeUpdate = HAL_GetTick();
}

enum SpeedType getSpeedType(Stepper *stepper)
{
    return stepper->speed.type;
}

void setSpeedType(Stepper *stepper, enum SpeedType type)
{
    stepper->speed.type = type;
}

enum SpeedState getSpeedState(Stepper *stepper)
{
    return stepper->speed.state;
}

void setSpeedState(Stepper *stepper, enum SpeedState state)
{
    stepper->speed.state = state;
}

/* END OF SPEED SECTION */

/* HARDWARE SECTION*/

TIM_HandleTypeDef *getSlaveTimer(Stepper *stepper)
{
    return &stepper->hardware.slaveTimer;
}

uint32_t getCurrentTarget(Stepper *stepper)
{
    return stepper->hardware.slaveTimer.Instance->ARR;
}

uint32_t getProgress(Stepper *stepper)
{
    return stepper->hardware.slaveTimer.Instance->CNT;
}

/* END OF HARDWARE SECTION */

enum State getState(Stepper *stepper)
{
    return stepper->state;
}

void setState(Stepper *stepper, enum State state)
{
    stepper->state = state;
}

uint8_t getDirection(Stepper *stepper)
{
    return HAL_GPIO_ReadPin(stepper->hardware.port, stepper->hardware.dir);
}