#include "command/cmd_executor.h"

#include <stdlib.h>

#include "null.h"
#include "validator.h"
#include "command/cmd_builder.h"

#include "process.h"
#include "device/device_manager.h"
#include "device/device_intervention.h"

#include "device/low_voltage/stepper/partial/stepper_validator.h"
#include "device/low_voltage/stepper/partial/stepper_configuration.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_intervention.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

#include "device/low_voltage/endstop/partial/endstop_operation.h"

#include "device/high_voltage/hvd.h"

#include "command/cmd_helper.h"

uint8_t *cmd_stepperAction(uint8_t *idx, uint8_t ***args, uint8_t **requiredKeys, uint8_t requiredKeysAmount, uint8_t (*validate)(Stepper *, uint8_t *, uint8_t *), void (*operate)(Stepper *, uint8_t *, uint8_t *), enum CMD_Type cmdType)
{
	uint8_t *feedback = EMPTY;
	uint8_t steppersCount = 0;
	uint8_t stepperIndex = 9;

	uint8_t i = 0;

	for (i = 0; i < requiredKeysAmount; i++)
	{
		if (validate_key(requiredKeys[i], args[i][0]) == ERR.ERROR)
		{
			feedback = cmd_builder_buildErr(idx, cmd_getErrorByKey(requiredKeys[i], KEY_ERROR));
			break;
		}
	}

	if (!stringLength(feedback))
	{
		steppersCount = cmd_getSteppersAmount(args[0][1]);

		if (steppersCount == 0)
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
		else
		{
			uint8_t end = steppersCount;
			uint8_t i = 0;
			uint8_t j = 0;

			if (steppersCount == 1)
			{
				stepperIndex = device_manager_getStepperIndex(args[0][1]);
				i = j = end = stepperIndex;
			}

			for (i; i <= end; i++)
			{
				Stepper *stepper = device_manager_getStepper(args[0][1]);

				uint8_t code = validate(stepper, args[1][1], args[2][1]);

				if (code != ERR.NO_ERROR)
				{
					feedback = cmd_builder_buildErr(idx, code);
					break;
				}
			}

			if (!stringLength(feedback))
			{
				for (j; j <= end; j++)
				{
					Stepper *stepper = device_manager_getStepper(args[0][1]);
					operate(stepper, args[1][1], args[2][1]);

					if (cmdType == LONG_TERM)
					{
						// check if move rly started (if endstop is already clicked it finish immediately)
						if (stepper_getState(stepper) == MOVING)
						{
							stepper_setIndex(stepper, idx);
							feedback = cmd_builder_buildPas(idx);
						}
						else
							feedback = cmd_builder_buildFin(idx);
					}
				}

				feedback = cmd_builder_buildFin(idx);
			}
		}
	}

	free(args);

	return feedback;
}

uint8_t *cmd_hvdAction(uint8_t *idx, uint8_t ***args, HVD *hvd)
{
	hvd_switch(hvd, args[0][1]);

	free(args);

	return cmd_builder_buildFin(idx);
}

uint8_t *cmd_proccessAction(uint8_t *idx, uint8_t **args)
{
	uint8_t *feedback = EMPTY;

	if (validate_key(KEY.DIRECTION, args[0][0]) == ERR.ERROR)
		feedback = cmd_builder_buildErr(idx, ERR.NO_DIRECTION_KEY);
	else
	{
		uint8_t code = process_validate(args[0][1]);

		if (code == ERR.NO_ERROR)
		{
			process_init(idx, convertStrToBoolean(args[0][1]));
			feedback = cmd_builder_buildPas(idx);
		}
		else
			feedback = cmd_builder_buildErr(idx, code);
	}

	free(args);

	return feedback;
}

uint8_t *cmd_getLVDState(uint8_t *idx, uint8_t ***args, enum LVD lvd)
{
	uint8_t *feedback = EMPTY;
	uint8_t devicesCount = 0;
	uint8_t deviceIndex = 9;
	uint8_t *states = "\0";

	if (validate_key(!lvd ? KEY.ENDSTOP : KEY.STEPPER, args[0][0]) == ERR.ERROR)
		feedback = cmd_builder_buildErr(idx, !lvd ? ERR.NO_ENDSTOP_KEY : ERR.NO_STEPPER_KEY);
	else
	{
		devicesCount = !lvd ? cmd_getEndstopsAmount(args[0][1]) : cmd_getSteppersAmount(args[0][1]);

		if (devicesCount == 0 || devicesCount == 2)
			feedback = cmd_builder_buildErr(idx, !lvd ? ERR.INVALID_ENDSTOP_VALUE : ERR.INVALID_STEPPER_VALUE);
		else
		{
			uint8_t end = devicesCount;
			uint8_t i = 0;

			if (devicesCount == 1)
			{
				deviceIndex = !lvd ? device_manager_getEndstopIndex(args[0][1]) : device_manager_getStepperIndex(args[0][1]);
				i = end = deviceIndex;
			}

			for (i; i <= end; i++)
			{
				if (!lvd)
				{
					Endstop *endstop = device_manager_getEndstop(args[0][1]);
					charAppend(states, endstop_isClicked(endstop));
				}
				else
				{
					Stepper *stepper = device_manager_getStepper(args[0][1]);
					charAppend(states, stepper_getState(stepper));
				}
			}

			feedback = cmd_builder_builRes(idx, states);
		}
	}

	free(args);

	return feedback;
}

uint8_t *cmd_getHVDState(uint8_t *idx, uint8_t ***args, HVD *hvd)
{
	uint8_t *state = hvd_getState(hvd);

	free(args);

	return cmd_builder_builRes(idx, state);
}
