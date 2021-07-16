#ifndef CONFIG_H
#define CONFIG_H

#define CLOCK_FREQUENCY 160000000 // main clock speed frequency

#define ENDSTOP_DEBOUNCE_TIME 20  // endstop debounce time in miliseconds (handle 'drganie stykow' service )
#define ENDSTOP_DEBOUNCE_AMOUNT 5 // endstop debounce amount needed to accept endstop clicked (handle 'drganie stykow' service )

#define STEPPER_SET_DIRECTION_DELAY 5 // delay time in microseconds after set direction of stepper before start move,  min 5us

#endif // CONFIG_H