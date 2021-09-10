#ifndef STEPPER_HELPER_H
#define STEPPER_HELPER_H

#include "device/low_voltage/stepper/stepper.h"

#include "device/low_voltage/stepper/enum/move_type.h"
#include "device/low_voltage/stepper/enum/speed_state.h"
#include "device/low_voltage/stepper/enum/speed_type.h"
#include "device/low_voltage/stepper/enum/state.h"

/* INFO SECTION */

// stepper->info.name
uint8_t stepper_getName(Stepper *stepper);

// stepper->info.index
uint8_t *stepper_getIndex(Stepper *stepper);
void stepper_setIndex(Stepper *stepper, uint8_t *index);

// stepper->info.state
enum State stepper_getState(Stepper *stepper);
void stepper_setState(Stepper *stepper, enum State state);

// stepper->info.invertedDirection
uint8_t stepper_isDirectionInverted(Stepper *stepper);

/* END OF INFO SECTION */

/* ACCELERATION SECTION */

// stepper->acceleration.current
float stepper_getCurrentAcceleration(Stepper *stepper);
void stepper_setCurrentAcceleration(Stepper *stepper, float acceleration);

// stepper->acceleration.stepsNeededToAccelerate
uint32_t stepper_getStepsNeededToAccelerate(Stepper *stepper);
void stepper_setStepsNeededToAccelerate(Stepper *stepper, uint32_t steps);

/* END OF ACCELERATION SECTION */

/* MOVEMENT */

// stepper->movement.rest
uint16_t stepper_getRest(Stepper *stepper);
void stepper_setRest(Stepper *stepper, uint16_t rest);

// stepper->movement.unloadedSteps
uint32_t stepper_getUnloadedSteps(Stepper *stepper);
void stepper_setUnloadedSteps(Stepper *stepper, uint32_t steps);

// stepper->movement.type
enum MoveType stepper_getMoveType(Stepper *stepper);
void stepper_setMoveType(Stepper *stepper, enum MoveType type);

// stepper->movement.direction
uint8_t stepper_getDirection(Stepper *stepper);

// stepper->movement.stepsPerUnit
float stepper_getStepsPerUnit(Stepper *stepper);

/* END OF INSTANCE SECTION */

/* SPEED SECTION */

// stepper->speed.current
float stepper_getCurrentSpeed(Stepper *stepper);
void stepper_setCurrentSpeed(Stepper *stepper, float speed);

// stepper->speed.current
float stepper_getTargetSpeed(Stepper *stepper);
void stepper_setTargetSpeed(Stepper *stepper, float speed);

// stepper->speed.lastTimeUpdate
uint32_t stepper_getLastTimeUpdate(Stepper *stepper);
void stepper_updateLastTime(Stepper *stepper);

// stepper->speed.type
enum SpeedType stepper_getSpeedType(Stepper *stepper);
void stepper_setSpeedType(Stepper *stepper, enum SpeedType type);

// stepper->speed.state
enum SpeedState stepper_getSpeedState(Stepper *stepper);
void stepper_setSpeedState(Stepper *stepper, enum SpeedState state);

/* END OF SPEED SECTION */

/* HARDWARE SECTION */

// stepper->hardware.slaveTimer
TIM_HandleTypeDef *stepper_getSlaveTimer(Stepper *stepper);

// stepper->hardware.slaveTimer.Instance.ARR
uint32_t stepper_getTarget(Stepper *stepper);

// stepper->hardware.slaveTimer.Instance.CNT
uint32_t stepper_getProgress(Stepper *stepper);

/* END OF HARDWARE SECTION */

#endif // STEPPER_HELPER_H
