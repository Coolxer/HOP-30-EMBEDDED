#ifndef APPLICATION_H
#define APPLICATION_H

#include "stm32f4xx.h"

void application_setup(); // setups all modules
void application_run(); // runs main application block
void application_close(); // closes all modules

void application_exec(); // calls setup, run & close functions

void SysTick_Handler(); // main SysTick function

#endif //APPLICATION_H