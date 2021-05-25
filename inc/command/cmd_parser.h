#ifndef CMD_PARSER
#define CMD_PARSER

#include <stdint.h> // includes uint8_t data type"

uint8_t ***cmd_parse(uint8_t *dialog); // explodes data and sparses it to 2d array, first column = key, second columns = value
                                       // [key],[value]
                                       // [opt],[move]
                                       // [spp],[x]

uint8_t *cmd_proceed(uint8_t ***args); // calls correct function depends on operation type (first row of the args; key:value e.g. opt=mov -> prepare_move())

/* PRIVATE */ // uint8_t *cmd_chooseAction(uint8_t *idx, uint8_t *opt, uint8_t ***args); // proceed operation and calls prepare function

#endif // CMD_PARSER