#ifndef DATA_ASSISTANT_H
#define DATA_ASSISTANT_H

#include <stdint.h>                                // includes uint8_t data type      


uint8_t* char_append(uint8_t *src, uint8_t ch);
uint8_t* str_append(uint8_t *src, uint8_t* str);
void data_clear(uint8_t *str);    // clears data array

#endif // DATA_ASSISTANT_H