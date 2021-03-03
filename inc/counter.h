#ifndef COUNTER_H
#define COUNTER_H

#include "stm32f4xx_hal.h"

/* own counter to replace HAL_Delay to more control and ability to delay with microseconds */
/* it is based on TIM_14 */

void counter_init();   // inits counter
void counter_deinit(); // deinits counter

void wait(uint16_t micros); // starts counting given time

#endif // COUNTER_H