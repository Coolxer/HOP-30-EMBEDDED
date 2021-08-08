#ifndef STATE_H
#define STATE_H

/* State of stepper
    * 0 - LOW - stepper is turned off, no holding torque
    * 1 - HIGH - stepper is turned on, keeping its position, waiting for action
    * 2 - MOVING - stepper is moving by given length 
    * 4 - PAUSED - stepper is paused, action can be RESUME or STOPPED
*/
enum State
{
    LOW = 0,
    HIGH = 1,
    MOVING = 2,
    PAUSED = 3
};

#endif // STATE_H
