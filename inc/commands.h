#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h> // includes uint8_t data type

#define CMD_COUNT 5
#define CMD_LENGTH 3

uint8_t tags[CMD_COUNT][CMD_LENGTH]=
{
    "opt", // operation
    "spp", // stepper
    "spd", // speed
    "stp", // steps
    "msp" // microstepping
};

uint8_t opts[4][3]=
{
	"set", //setup
  	"sth", //switch (turn off/on stepper motor)
  	"mov", //move
  	"pro" // process
};

#endif // COMMANDS_H 
