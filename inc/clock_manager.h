#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

/* PRIVATE */                //void clock_manager_config(); // setups main clock frequency
void clock_manager_init();   // enables all necessary clocks
void clock_manager_deinit(); // disables all necessary clocks

#endif // CLOCK_MANAGER_H
