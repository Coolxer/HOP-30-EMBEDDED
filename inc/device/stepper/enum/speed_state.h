#ifndef SPEED_STATE_H
#define SPEED_STATE_H

/* Current speed state (behaviour)
    * 0 - RAISING - speed is raising (going up)
    * 0 - CONSTANT - speed is constant
    * 1 - FALLING - speed is falling down
*/
enum SpeedState
{
    RAISING = 0,
    CONSTANT = 1,
    FALLING = 2,
    NONE = 3
};

#endif // SPEED_STATE_H
