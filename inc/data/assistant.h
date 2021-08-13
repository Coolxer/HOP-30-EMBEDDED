#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <stdint.h> // includes uint8_t data type

uint8_t stringLength(uint8_t *str);                // returns string length
uint8_t stringEqual(uint8_t *str1, uint8_t *str2); // returns true if string equals

void clearString(uint8_t *src, uint8_t len);    // clears whole string
uint8_t *charAppend(uint8_t *src, uint8_t ch);  // appends char to given string
uint8_t *strAppend(uint8_t *src, uint8_t *str); // appends string to given string

uint8_t convertStrToBoolean(uint8_t *str); // converts str to boolean
float convertStrToFloat(uint8_t *str);     // converts str to float

uint8_t containsOnlyDigits(uint8_t *str); // checks if string contains only digits, if only numbers returns true

#endif // ASSISTANT_H