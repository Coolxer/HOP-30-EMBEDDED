#ifndef SPEED_STATE_H
#define SPEED_STATE_H

/* Current speed state (behaviour)
    * 0 - RAISING - speed is raising (going up)
    * 1 - CONSTANT - speed is constant
    * 2 - FALLING - speed is falling down
*/
enum SpeedState
{
    RAISING = 0,
    CONSTANT = 1,
    FALLING = 2
};

#endif // SPEED_STATE_H
