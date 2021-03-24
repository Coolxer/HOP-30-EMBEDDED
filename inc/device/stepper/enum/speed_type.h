#ifndef SPEED_TYPE_H
#define SPEED_TYPE_H

/* Speed type (behaviour)
    * 0 - STATIC - speed is static (constant, no acceleration)
    * 1 - DYNAMIC - speed is raising / falling (with acceleration)
*/
enum SpeedType
{
    STATIC = 0,
    DYNAMIC = 1,
};

#endif // SPEED_TYPE_H
