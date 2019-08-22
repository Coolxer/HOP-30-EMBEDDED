#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <stdint.h> // includes uint8_t data type

#define DATA_SIZE 64 // size of data transmission 

#define DIALOG_DELIMITER "|" 
#define PARAM_DELIMITER "="
#define SPACE_FILLER '~'

uint8_t data[DATA_SIZE]; // array using for receiving data and stores messages

//const uint8_t DIALOG_DELIMITER = '|'; // the dialog delimiter, that seprates 2 sentences; e.g. opt=mov|spp=s1|
//const uint8_t PARAM_DELIMITER = '='; // the param (sentence) delimiter, that seperate key and value of sentence; e.g. opt=mov

uint8_t ***connector_parse(uint8_t * size); // explodes data and parses it to 2d array, first column = key, second columns = value
                                             // [key],[value]
                                             // [opt],[move]
                                             // [spp],[s1]                            

void connector_manage_data(uint8_t ***args, uint8_t* size); // calls correct function depends on operation type (first row of the args; key:value e.g. opt=mov -> prepare_move()) 

uint8_t connector_string_size(uint8_t *string); // returns size of array of uint8_t (size of string)

void connector_start(); // parse dialog with connector_parse() and passes it to connector_manage_data()

void connector_build_data(); // fills in SPACE_FILLER to data array into free spaces
void connector_cut_data(); // removes SPACE_FILLER's from data array
void connector_clear_data(); // clears data array

uint8_t connector_string_equals(uint8_t string[]); // compares data and string; if equals returns 0; else <0 or >0

#endif // CONNECTOR_H