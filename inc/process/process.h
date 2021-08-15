#ifndef PROCESS_H
#define PROCESS_H

enum ProcessState
{
    NONE = 0,
    FORWARD = 1,
    BACKWARD = 2,
    HALTED = 3
};

extern volatile enum ProcessState PROCESS_STATE;
extern volatile enum ProcessState PROCESS_PREVIOUS_STATE;

extern volatile uint8_t COOLANT_ENABLE;

#endif // PROCESS_H