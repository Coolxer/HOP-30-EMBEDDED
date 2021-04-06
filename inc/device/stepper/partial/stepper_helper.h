#ifndef STEPPER_HELPER_H
#define STEPPER_HELPER_H

#include "device/stepper/stepper.h"

#include "device/stepper/enum/axis_type.h"

#include "device/stepper/enum/state.h"
#include "device/stepper/enum/home_step.h"

#include "device/stepper/enum/speed_type.h"
#include "device/stepper/enum/speed_state.h"

/* INFO SECTION */

// stepper->info.axisType
enum AxisType getAxisType(Stepper *stepper);

// stepper->info.name
uint8_t *getName(Stepper *stepper);

// stepper->info.index
uint8_t *getIndex(Stepper *stepper);
void setIndex(Stepper *stepper, uint8_t *index);

/* END OF INFO SECTION */

/* ACCELERATION SECTION */

// stepper->acceleration.min
float getMinAcceleration(Stepper *stepper);

// stepper->acceleration.max
float getMaxAcceleration(Stepper *stepper);

// stepper->acceleration.current
float getCurrentAcceleration(Stepper *stepper);
void setCurrentAcceleration(Stepper *stepper, float acceleration);

// stepper->acceleration.homeFastBackward
float getHomeFastBackwardAcceleration(Stepper *stepper);

// stepper->acceleration.homeSlowForward
float getHomeSlowForwardAcceleration(Stepper *stepper);

// stepper->acceleration.homePreciseBackward
float getHomePreciseBackwardAcceleration(Stepper *stepper);

// stepper->acceleration.stepsNeededToAccelerate
uint32_t getStepsNeededToAccelerate(Stepper *stepper);
void setStepsNeededToAccelerate(Stepper *stepper, uint32_t steps);

/* END OF ACCELERATION SECTION */

/* INSTANCE SECTION */

// stepper->instance.state
enum State getState(Stepper *stepper);
void setState(Stepper *stepper, enum State state);

// stepper->instance.lastState
enum State getLastState(Stepper *stepper);
void updateLastState(Stepper *stepper);

// stepper->instance.homeStep
enum HomeStep getHomeStep(Stepper *stepper);
void setHomeStep(Stepper *stepper, enum HomeStep step);

/* MOVEMENT */

// stepper->movement.rest
uint16_t getRest(Stepper *stepper);
void setRest(Stepper *stepper, uint16_t rest);

// stepper->movement.target
uint32_t getTarget(Stepper *stepper);
void setTarget(Stepper *stepper, uint32_t target);

/* END OF INSTANCE SECTION */

/* SPEED SECTION */

// stepper->speed.min
float getMinSpeed(Stepper *stepper);

// stepper->speed.max
float getMaxSpeed(Stepper *stepper);

// stepper->speed.current
float getCurrentSpeed(Stepper *stepper);
void setCurrentSpeed(Stepper *stepper, float speed);

// stepper->speed.current
float getTargetSpeed(Stepper *stepper);
void setTargetSpeed(Stepper *stepper, float speed);

// stepper->speed.homeFastBackward
float getHomeFastBackwardSpeed(Stepper *stepper);

// stepper->speed.homeSlowForward
float getHomeSlowForwardSpeed(Stepper *stepper);

// stepper->speed.homePreciseBackward
float getHomePreciseBackwardSpeed(Stepper *stepper);

// stepper->speed.lastTimeUpdate
uint32_t getLastTimeUpdate(Stepper *stepper);
void updateLastTime(Stepper *stepper);

// stepper->speed.type
enum SpeedType getSpeedType(Stepper *stepper);
void setSpeedType(Stepper *stepper, enum SpeedType type);

// stepper->speed.state
enum SpeedState getSpeedState(Stepper *stepper);
void setSpeedState(Stepper *stepper, enum SpeedState state);

/* END OF SPEED SECTION */

/* HARDWARE SECTION */

// stepper->hardware.slaveTimer
TIM_HandleTypeDef *getSlaveTimer(Stepper *stepper);

// stepper->hardware.slaveTimer.Instance.ARR
uint32_t getCurrentTarget(Stepper *stepper);

// stepper->hardware.slaveTimer.Instance.CNT
uint32_t getProgress(Stepper *stepper);

/* END OF HARDWARE SECTION */

uint8_t getDirection(Stepper *stepper);

#endif // STEPPER_HELPER_H
