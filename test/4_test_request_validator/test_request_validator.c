#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>

#include "stm32f4xx_hal.h"

#include "command/cmd_manager.h"
#include "command/request/request.h"

#include "command/request/request_parser.h"
#include "command/request/request_validator.h"

void setUp()
{
    cmd_manager_init();
}

void tearDown();

// check general things

void test_request_checkGeneralThings_should_give_no_params_error()
{
    uint8_t data[] = "aaaaaaaaaaaaaaa|\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_UINT8(ERR.NO_PARAMS, request_checkGeneralThings(args, records));
}

void test_request_checkGeneralThings_should_give_one_param_only_error()
{
    uint8_t data[] = "opt=aaaaaaaaaa|\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_UINT8(ERR.ONE_PARAM_ONLY, request_checkGeneralThings(args, records));
}

void test_request_checkGeneralThings_should_give_to_many_params_error()
{
    uint8_t data[] = "abc=123|spp=12|spd=1|alf=56|afk=3|dfg=3\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_UINT8(ERR.TO_MANY_PARAMS, request_checkGeneralThings(args, records));
}

void test_request_checkGeneralThings_should_give_no_index_key_error()
{
    uint8_t data[] = "abc=123|spp=12|spd=1|\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_UINT8(ERR.NO_INDEX_KEY, request_checkGeneralThings(args, records));
}

void test_request_checkGeneralThings_should_give_invalid_index_value_error()
{
    uint8_t data[] = "idx=ab|spp=12|spd=1|\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_UINT8(ERR.INVALID_INDEX_VALUE, request_checkGeneralThings(args, records));
}

void test_request_checkGeneralThings_should_give_no_operation_key_error()
{
    uint8_t data[] = "idx=3|spp=12|spd=1|\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_UINT8(ERR.NO_OPERATION_KEY, request_checkGeneralThings(args, records));
}

void test_request_checkGeneralThings_should_give_no_error()
{
    uint8_t data[] = "idx=3|opt=cfs|spp=12|spd=1|\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, request_checkGeneralThings(args, records));
}

// validate keys

void test_request_validate_keys_shoud_give_no_key_error()
{
    uint8_t data[] = "idx=3|opt=cfs|spa=x|spd=1|\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    Request request = {0};

    request.requiredKeys[0] = KEY.STEPPER;
    request.requiredKeysAmount = 1;

    TEST_ASSERT_EQUAL_UINT8(ERR.NO_STEPPER_KEY, request_validateRequestKeys(args, request.requiredKeys, request.requiredKeysAmount));
}

void test_request_validate_keys_shoud_give_no_error()
{
    uint8_t data[] = "idx=3|opt=cfs|spp=x|spd=1|acc=non|\n";
    uint8_t records = 0;

    uint8_t ***args = request_explode(data, &records);

    Request request = {0};

    request.requiredKeys[0] = KEY.STEPPER;
    request.requiredKeys[1] = KEY.SPEED;
    request.requiredKeys[2] = KEY.ACCELERATION;

    request.requiredKeysAmount = 3;

    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, request_validateRequestKeys(args, request.requiredKeys, request.requiredKeysAmount));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_request_checkGeneralThings_should_give_no_params_error);
    RUN_TEST(test_request_checkGeneralThings_should_give_one_param_only_error);
    RUN_TEST(test_request_checkGeneralThings_should_give_to_many_params_error);
    RUN_TEST(test_request_checkGeneralThings_should_give_no_index_key_error);
    RUN_TEST(test_request_checkGeneralThings_should_give_invalid_index_value_error);
    RUN_TEST(test_request_checkGeneralThings_should_give_no_operation_key_error);
    RUN_TEST(test_request_checkGeneralThings_should_give_no_error);

    //RUN_TEST(test_request_validate_keys_shoud_give_no_key_error);
    //RUN_TEST(test_request_validate_keys_shoud_give_no_error);

    UNITY_END();
}

#endif // UNIT_TEST