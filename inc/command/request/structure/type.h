#ifndef TYPE_H
#define TYPE_H

/*
    RequestType descripe type of request
    INSTANT -> for configuration commands mostly
    LONG_TERM -> for stepper moving and process
    ANSWER -> for gather devices states map
*/

enum RequestType
{
    INSTANT = 1,
    LONG_TERM = 2,
    ANSWER = 3
};

#endif // TYPE_H