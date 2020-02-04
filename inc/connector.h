#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <stdint.h>                                               // includes uint8_t data type" 

// extern uint8_t *dialog_delimiter;                                 // the dialog delimiter, that seprates 2 sentences; e.g. opt=mov|spp=x|
// extern uint8_t *param_delimiter;                                  // the param (sentence) delimiter, that seperate key and value of sentence; e.g. opt=mov

uint8_t records;                                                  // number of rows (key:value) of parsered dialog 

uint8_t ***connector_parse(uint8_t *dialog);                      // explodes data and sparses it to 2d array, first column = key, second columns = value
                                                                  // [key],[value]
                                                                  // [opt],[move]
                                                                  // [spp],[s1]                            

uint8_t *connector_manage_data(uint8_t ***args); // calls correct function depends on operation type (first row of the args; key:value e.g. opt=mov -> prepare_move()) 

#endif // CONNECTOR_H