#include "prepare_function.h"

#include <stdlib.h>

#include "null.h"
#include "validator.h"
#include "command/cmd_builder.h"

#include "process.h"
#include "device/device_intervention.h"

#include "device/stepper/partial/stepper_validator.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_operation.h"
#include "device/stepper/partial/stepper_intervention.h"
#include "device/stepper/partial/stepper_helper.h"

// e.g [spp=x|spd=14.16|acc=1.0]
// e.g [spp=x|spd=14.16|acc=non]
uint8_t *prepare_configure(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = EMPTY;

	if (validate_key(KEY.STEPPER, args[0][0]) == ERR.ERROR)
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);
	else
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
		else
		{
			if (validate_key(KEY.SPEED, args[1][0]) == ERR.ERROR)
				feedback = cmd_builder_buildErr(idx, ERR.NO_SPEED_KEY);
			else
			{
				if (validate_key(KEY.ACCELERATION, args[2][0]) == ERR.ERROR)
					feedback = cmd_builder_buildErr(idx, ERR.NO_ACCELERATION_KEY);
				else
				{
					uint8_t code = validate_configure(stepper, args[1][1], args[2][1]);

					if (code == ERR.NO_ERROR)
					{
						stepper_configure(stepper, convertStrToFloat(args[1][1]), stringEqual(args[2][1], VAL.NONE) ? 0.0f : convertStrToFloat(args[2][1]));
						feedback = cmd_builder_buildFin(idx);
					}
					else
						feedback = cmd_builder_buildErr(idx, code);
				}
			}
		}
	}

	free(args);

	return feedback;
}

// e.g [spp=x|stt=1]
uint8_t *prepare_switch(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = EMPTY;

	if (validate_key(KEY.STEPPER, args[0][0]) == ERR.ERROR)
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);
	else
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
		else
		{
			if (validate_key(KEY.STATE, args[1][0]) == ERR.ERROR)
				feedback = cmd_builder_buildErr(idx, ERR.NO_STATE_KEY);
			else
			{
				uint8_t code = validate_switch(stepper, args[1][1]);

				if (code == ERR.NO_ERROR)
				{
					stepper_switch(stepper, convertStrToBoolean(args[1][1]));
					feedback = cmd_builder_buildFin(idx);
				}
				else
					feedback = cmd_builder_buildErr(idx, code);
			}
		}
	}

	free(args);

	return feedback;
}

// e.g [spp=x|way=30|dir=0]
// e.g [spp=x|way=lim|dir=0]
uint8_t *prepare_move(uint8_t *idx, uint8_t ***args)
{
	Stepper *stepper = NULL;
	uint8_t *feedback = EMPTY;

	if (validate_key(KEY.STEPPER, args[0][0]) == ERR.ERROR)
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);
	else
	{
		if (!(stepper = device_manager_getStepper(args[0][1])))
			feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
		else
		{
			if (validate_key(KEY.WAY, args[1][0]) == ERR.ERROR)
				feedback = cmd_builder_buildErr(idx, ERR.NO_WAY_KEY);
			else
			{
				if (validate_key(KEY.DIRECTION, args[2][0]) == ERR.ERROR)
					feedback = cmd_builder_buildErr(idx, ERR.NO_DIRECTION_KEY);
				else
				{
					uint8_t code = validate_move(stepper, args[1][1], args[2][1]);

					if (code == ERR.NO_ERROR)
					{
						stepper_move(stepper, stringEqual(args[1][1], VAL.LIMIT) ? 0.0f : convertStrToFloat(args[1][1]), convertStrToBoolean(args[2][1]));

						// check if move rly started (if endstop is already clicked it finish immediately)
						if (stepper_getState(stepper) == MOVING)
						{
							stepper_setIndex(stepper, idx);
							feedback = cmd_builder_buildPas(idx);
						}
						else
							feedback = cmd_builder_buildFin(idx);
					}
					else
						feedback = cmd_builder_buildErr(idx, code);
				}
			}
		}
	}

	free(args);

	return feedback;
}

// e.g [dir=1]
uint8_t *prepare_process(uint8_t *idx, uint8_t ***args)
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

// prepare pause, resume or stop
// e.g [spp=x]
uint8_t *prepare_intervention(uint8_t *idx, uint8_t ***args, void (*intervene)(Stepper *), uint8_t (*validate)(Stepper *))
{
	Stepper *stepper = NULL;
	uint8_t *feedback = EMPTY;

	if (validate_key(KEY.STEPPER, args[0][0]) == ERR.ERROR)
		feedback = cmd_builder_buildErr(idx, ERR.NO_STEPPER_KEY);
	else
	{
		if (stringEqual(args[0][1], VAL.PROCESS)) // group of steppers that consists of process (x & w)
		{
			intervene_process(intervene);
			feedback = cmd_builder_buildFin(idx);
		}
		else if (stringEqual(args[0][1], VAL.ALL)) // all steppers (x, y, z, w, k)
		{
			intervene_all(intervene);
			feedback = cmd_builder_buildFin(idx);
		}
		else // if individual stepper
		{
			if (!(stepper = device_manager_getStepper(args[0][1])))
				feedback = cmd_builder_buildErr(idx, ERR.INVALID_STEPPER_VALUE);
			else
			{
				uint8_t code = validate(stepper);

				if (code == ERR.NO_ERROR)
				{
					intervene(stepper);
					feedback = cmd_builder_buildFin(idx); // SUCCESS
				}
				else
					feedback = cmd_builder_buildErr(idx, code);
			}
		}
	}

	free(args);

	return feedback;
}