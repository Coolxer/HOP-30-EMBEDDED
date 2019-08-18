#ifndef UART_MIN_H
#define UART_MIN_H

#include <string.h> // includes defintion of strtok function
#include <stdint.h> // includes uint8_t data type
#include <stddef.h> // includes NULL value

const uint8_t DIALOG_DELIMITER = '|'; // the dialog delimiter, that seprates 2 sentences; e.g. opt=mov|spp=s1|
const uint8_t PARAM_DELIMITER = '='; // the param (sentence) delimiter, that seperate key and value of sentence; e.g. opt=mov

uint8_t ***connector_parse(uint8_t *dialog); // explodes data and parses it to 2d array, first column = key, second columns = value
                                             // [key],[value]
                                             // [opt],[move]
                                             // [spp],[s1]

void connector_manage_data(uint8_t ***args); // calls correct function depends on operation type (first row of the args; key:value e.g. opt=mov -> prepare_move()) 

uint8_t connector_string_size(uint8_t *string); // returns size of array of uint8_t (size of string)
uint8_t connector_data_size(uint8_t ***args); // return size of 2d array of uint8_t

#endif // UART_MIN_H