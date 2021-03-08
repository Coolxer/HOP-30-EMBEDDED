#ifndef HOME_STEP_H
#define HOME_STEP_H

/* Step of home operation
    * 0 - FAST - normal going to the endstop
    * 1 - BACKWARD - outgoing from endstop by given number of steps, to "unclick" the endstop
    * 2 - PRECISE - slow, precise going until endstop clicked
*/
enum HomeStep
{
    FAST = 0,
    BACKWARD = 1,
    PRECISE = 2
};

#endif // HOME_STEP_H
