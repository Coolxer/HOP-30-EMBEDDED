#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdint.h>

uint8_t ***request_explode(uint8_t *request, uint8_t *recs);

#endif // REQUEST_PARSER_H