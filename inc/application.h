#ifndef APPLICATION_H
#define APPLICATION_H

#include "stm32f4xx.h"

/* PRIVATE */   //void application_setup(); // setups all modules
/* PRIVATE */   //void application_run();   // runs main application loop
/* PRIVATE */   //void application_close(); // closes all modules

void application_exec();  // calls setup, run & close functions

/* PRIVATE */   //void SysTick_Handler();   // main SysTick function

#endif //APPLICATION_H