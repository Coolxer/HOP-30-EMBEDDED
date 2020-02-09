#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <stdint.h>                                               // includes uint8_t data type"      

uint8_t ***connector_parse(uint8_t *dialog);                      // explodes data and sparses it to 2d array, first column = key, second columns = value
                                                                  // [key],[value]
                                                                  // [opt],[move]
                                                                  // [spp],[s1]                            

uint8_t *connector_manageData(uint8_t ***args);                  // calls correct function depends on operation type (first row of the args; key:value e.g. opt=mov -> prepare_move()) 

#endif // CONNECTOR_H