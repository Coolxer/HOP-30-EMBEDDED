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

float getMinAcceleration(Stepper *stepper)
{
    return stepper->acceleration.min;
}

float getMaxAcceleration(Stepper *stepper)
{
    return stepper->acceleration.max;
}

float getCurrentAcceleration(Stepper *stepper)
{
    return stepper->acceleration.current;
}

void setCurrentAcceleration(Stepper *stepper, float acceleration)
{
    stepper->acceleration.current = acceleration;
}

float getHomeFastBackwardAcceleration(Stepper *stepper)
{
    return stepper->acceleration.homeFastBackward;
}

float getHomeSlowForwardAcceleration(Stepper *stepper)
{
    return stepper->acceleration.homeSlowForward;
}

float getHomePreciseBackwardAcceleration(Stepper *stepper)
{
    return stepper->acceleration.homePreciseBackward;
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

/* INSTANCE SECTION */

enum State getState(Stepper *stepper)
{
    return stepper->instance.state;
}

void setState(Stepper *stepper, enum State state)
{
    stepper->instance.state = state;
}

enum State getLastState(Stepper *stepper)
{
    return stepper->instance.lastState;
}

void updateLastState(Stepper *stepper)
{
    stepper->instance.lastState = stepper->instance.state;
}

enum HomeStep getHomeStep(Stepper *stepper)
{
    return stepper->instance.homeStep;
}

void setHomeStep(Stepper *stepper, enum HomeStep step)
{
    stepper->instance.homeStep = step;
}

/* END OF INSTANCE SECTION */

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

/* END OF MOVEMENT SECTION */

/* SPEED SECTION */

float getMinSpeed(Stepper *stepper)
{
    return stepper->speed.min;
}

float getMaxSpeed(Stepper *stepper)
{
    return stepper->speed.max;
}

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

float getHomeFastBackwardSpeed(Stepper *stepper)
{
    return stepper->speed.homeFastBackward;
}

float getHomeSlowForwardSpeed(Stepper *stepper)
{
    return stepper->speed.homeSlowForward;
}

float getHomePreciseBackwardSpeed(Stepper *stepper)
{
    return stepper->speed.homePreciseBackward;
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

uint8_t getDirection(Stepper *stepper)
{
    return HAL_GPIO_ReadPin(stepper->hardware.port, stepper->hardware.dir);
}