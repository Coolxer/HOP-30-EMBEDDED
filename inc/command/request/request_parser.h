#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdint.h>

extern uint8_t records;

uint8_t *request_truncate(uint8_t *request);
uint8_t ***request_explode(uint8_t *request);

#endif // REQUEST_PARSER_H