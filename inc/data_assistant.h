#ifndef DATA_ASSISTANT_H
#define DATA_ASSISTANT_H

#include <stdint.h>

#define DATA_SIZE 64                          // size of data transmission 
#define SPACE_FILLER '~'                      // sign using for fill in free spaces

uint8_t data[DATA_SIZE];                      // array using for receiving data and stores messages

uint8_t data_string_size(uint8_t *string);    // returns size of array of uint8_t (size of string)
void data_build();                            // fills in SPACE_FILLER to data array into free spaces
void data_cut();                              // removes SPACE_FILLER's from data array
void data_clear();                            // clears data array
uint8_t data_string_equals(uint8_t string[]); // compares data and string; if equals returns 0; else <0 or >0

#endif // DATA_ASSISTANT_H