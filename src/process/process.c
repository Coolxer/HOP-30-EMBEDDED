#include "process/process.h"

volatile enum ProcessState PROCESS_STATE = NONE;
volatile enum ProcessState PROCESS_PREVIOUS_STATE = NONE;
