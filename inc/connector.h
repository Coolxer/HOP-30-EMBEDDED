#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "data_assistant.h"

#define DIALOG_DELIMITER "|" 
#define PARAM_DELIMITER "="

//const uint8_t DIALOG_DELIMITER = '|'; // the dialog delimiter, that seprates 2 sentences; e.g. opt=mov|spp=s1|
//const uint8_t PARAM_DELIMITER = '='; // the param (sentence) delimiter, that seperate key and value of sentence; e.g. opt=mov

uint8_t ***connector_parse(uint8_t * size); // explodes data and parses it to 2d array, first column = key, second columns = value
                                            // [key],[value]
                                            // [opt],[move]
                                            // [spp],[s1]                            

void connector_manage_data(uint8_t ***args, uint8_t* size); // calls correct function depends on operation type (first row of the args; key:value e.g. opt=mov -> prepare_move()) 

void connector_start(); // parse dialog with connector_parse() and passes it to connector_manage_data()

#endif // CONNECTOR_H