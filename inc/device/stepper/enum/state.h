#ifndef STATE_H
#define STATE_H

/* State of stepper
    * 0 - OFF - stepper is turned off, no holding torque
    * 1 - ON - stepper is turned on, keeping its position, waiting for action
    * 2 - HOMING - stepper is homing 
    * 3- MOVING - stepper is moving by given length 
    * 4- PAUSED - stepper is paused, action can be RESUME or STOPPED
*/
enum State
{
    OFF = 0,
    ON = 1,
    HOMING = 2,
    MOVING = 3,
    PAUSED = 4
};

#endif // STATE_H