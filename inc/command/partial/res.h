#ifndef RES_H
#define RES_H

#include <stdint.h>

struct res
{
    uint8_t PASSED[4],
        ERR[4],
        FINISHED[4];
} RES;

void res_init();

#endif // RES_H