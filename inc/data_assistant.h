#ifndef DATA_ASSISTANT_H
#define DATA_ASSISTANT_H

#include <stdint.h>                           // includes uint8_t data type              

#define SPACE_FILLER '~'                      // sign using for fill in free spaces                 

uint8_t data_length(uint8_t *dt);             // returns real length of the string
uint8_t data_size(uint8_t *dt);               // returns size of array of uint8_t (in bytes)
void data_build(uint8_t *dt);                 // fills in SPACE_FILLER to data array into free spaces
void data_cut(uint8_t *dt);                   // removes SPACE_FILLER's from data array
void data_clear(uint8_t *dt);                 // clears data array
uint8_t data_equal(uint8_t *s1, uint8_t *s2); // compares data and string; if equals returns 0; else <0 or >0

#endif // DATA_ASSISTANT_H