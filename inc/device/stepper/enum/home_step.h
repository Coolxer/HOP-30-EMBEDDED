#ifndef HOME_STEP_H
#define HOME_STEP_H

/* Step of home operation
    * 0 - FAST_BACKWARD - normal going to the min endstop
    * 1 - SLOW_FORWARD - outgoing from endstop by given number of steps, to "unclick" the endstop
    * 2 - PRECISE_BACKWARD - slow, precise going until endstop clicked
*/
enum HomeStep
{
    FAST_BACKWARD = 0,
    SLOW_FORWARD = 1,
    PRECISE_BACKWARD = 2
};

#endif // HOME_STEP_H
