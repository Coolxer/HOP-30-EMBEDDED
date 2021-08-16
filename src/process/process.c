#include "process/process.h"

volatile enum ProcessState PROCESS_STATE = NONE;
volatile enum ProcessState PROCESS_PREVIOUS_STATE = NONE;

volatile uint8_t COOLANT_ENABLE = 0;

volatile uint8_t PROCESS_CONFIGURED = 0;
