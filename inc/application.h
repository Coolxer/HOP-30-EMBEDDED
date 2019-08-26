#ifndef APPLICATION_H
#define APPLICATION_H

void application_setup(); // setups all modules
void application_run(); // runs main application block
void application_close(); // closes all modules

void application_exec(); // calls setup, run & close functions

#endif //APPLICATION_H