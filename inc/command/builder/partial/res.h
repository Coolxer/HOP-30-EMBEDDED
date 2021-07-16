#ifndef RES_H
#define RES_H

#include <stdint.h>

typedef struct
{
    uint8_t ERROR[4],
        PASSED[4],
        IN_PROGRESS[4],
        FINISHED[4],
        VALUE[4];
} res;

extern res RES;

void res_init();

#endif // RES_H