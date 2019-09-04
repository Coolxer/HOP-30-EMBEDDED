#ifndef DATA_ASSISTANT_H
#define DATA_ASSISTANT_H

#include <stdint.h> // includes uint8_t data type      

#define SPACE_FILLER '~' // space sign which is using to fill in blanks

void data_fullfill(uint8_t dt[], uint8_t dt_size); // fills in SPACE_FILLER to data array into free spaces
void data_crop(uint8_t dt[], uint8_t dt_size); // removes SPACE_FILLER's from data array
void data_clear(uint8_t dt[], uint8_t dt_size); // clears data array

#endif // DATA_ASSISTANT_H