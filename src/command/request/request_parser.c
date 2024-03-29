#include "command/request/request_parser.h"

#include <string.h>
#include <stdlib.h>

#include "null.h"

uint8_t *cmd_delimiter = (uint8_t *)"|";   // the cmd delimiter, that seprates 2 sentences; e.g. opt=mov|spp=x|
uint8_t *param_delimiter = (uint8_t *)"="; // the param (sentence) delimiter, that seperate key and value of sentence; e.g. opt=mov

uint8_t ***request_explode(uint8_t *request, uint8_t *recs)
{
    uint8_t ***args = NULL, *param = NULL, *key = NULL, *value = NULL;

    uint8_t records = 0; // number of records (rows) with 2 columns: key:value

    for (param = (uint8_t *)strtok((void *)request, (void *)cmd_delimiter); param != NULL; param = (uint8_t *)strtok(NULL, (void *)cmd_delimiter))
    {
        if (param[0] == '=' || strchr((void *)param, *param_delimiter) == NULL)
            break;

        key = (uint8_t *)strtok_r((void *)param, (void *)param_delimiter, (void *)&value); // assigns key & values contents
        args = (uint8_t ***)realloc(args, (++records) * sizeof(uint8_t *));                // extends array by one row (2 columns)

        args[records - 1] = (uint8_t **)malloc(2 * sizeof(uint8_t *));                   // reserves memory for one row with 2 columns
        args[records - 1][0] = (uint8_t *)malloc((sizeof(key) * 8) * sizeof(uint8_t));   // reserves memory for key column
        args[records - 1][1] = (uint8_t *)malloc((sizeof(value) * 8) * sizeof(uint8_t)); // reserves memory for value column

        strcpy((void *)args[records - 1][0], (void *)key);   // copy  key string to the array
        strcpy((void *)args[records - 1][1], (void *)value); // copies value string to the array
    }

    *recs = records;

    return args; // returns 2d array of array of uint8_t
}