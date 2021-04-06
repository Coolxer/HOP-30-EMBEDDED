#ifndef MOVE_TYPE_H
#define MOVE_TYPE_H

/* Move type 
    * 0 - LIMITED - move until endstop clicked
    * 1 - PRECISED - move by given value (can be also broken by endstop)
*/
enum MoveType
{
    LIMITED = 0,
    PRECISED = 1,
};

#endif // MOVE_TYPE_H
