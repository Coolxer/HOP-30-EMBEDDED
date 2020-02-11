#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    device_manager_init();
}

void tearDown(); // default release function


/*********************** prepare_intervention pause ***************************************/

// common
void test_prepare_intervention_pause_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=pau|abc=x|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

// pause pro
void test_prepare_intervention_pause_pro_should_give_success()
{
    uint8_t data[] = "opt=pau|spp=pro|mod=0|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

// pause all
void test_prepare_intervention_pause_all_should_give_success()
{
    uint8_t data[] = "opt=pau|spp=all|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

// pause individual
void test_prepare_intervention_pause_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=pau|spp=a|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", result);
}

void test_prepare_intervention_pause_should_give_no_mod_key_error()
{
    uint8_t data[] = "opt=pau|spp=x|abc=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_mod_key", result);
}

void test_prepare_intervention_pause_should_give_invalid_mod_value_error()
{
    uint8_t data[] = "opt=pau|spp=x|mod=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_mod_value", result);
}

void test_prepare_intervention_pause_should_give_success()
{
    uint8_t data[] = "opt=pau|spp=x|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

/*********************** prepare_intervention resume ***************************************/

// common
void test_prepare_intervention_resume_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=res|abc=x|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

// resume pro
void test_prepare_intervention_resume_pro_should_give_success()
{
    uint8_t data[] = "opt=res|spp=pro|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

// resume all
void test_prepare_intervention_resume_all_should_give_success()
{
    uint8_t data[] = "opt=res|spp=all|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

// resume individual
void test_prepare_intervention_resume_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=res|spp=a|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", result);
}

void test_prepare_intervention_resume_should_give_no_mod_key_error()
{
    uint8_t data[] = "opt=res|spp=x|abc=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_mod_key", result);
}

void test_prepare_intervention_resume_should_give_invalid_mod_value_error()
{
    uint8_t data[] = "opt=res|spp=x|mod=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_mod_value", result);
}

void test_prepare_intervention_resume_should_give_success()
{
    uint8_t data[] = "opt=res|spp=x|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

/*********************** prepare_intervention stop ***************************************/

// common
void test_prepare_intervention_stop_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=sto|abc=x|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

// stop pro
void test_prepare_intervention_stop_pro_should_give_success()
{
    uint8_t data[] = "opt=sto|spp=pro|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

// stop all
void test_prepare_intervention_stop_all_should_give_success()
{
    uint8_t data[] = "opt=sto|spp=all|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

// stop individual

void test_prepare_intervention_stop_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=sto|spp=a|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", result);
}

void test_prepare_intervention_stop_should_give_no_mod_key_error()
{
    uint8_t data[] = "opt=sto|spp=x|abc=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_mod_key", result);
}

void test_prepare_intervention_stop_should_give_invalid_mod_value_error()
{
    uint8_t data[] = "opt=sto|spp=x|mod=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_mod_value", result);
}

void test_prepare_intervention_stop_should_give_success()
{
    uint8_t data[] = "opt=sto|spp=x|mod=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    /***************** prepare intervention pause ********************/

    RUN_TEST(test_prepare_intervention_pause_should_give_no_spp_key_error);

    // pause pro
    RUN_TEST(test_prepare_intervention_pause_pro_should_give_success);

    // pause all
    RUN_TEST(test_prepare_intervention_pause_all_should_give_success);

    // pause individual
    RUN_TEST(test_prepare_intervention_pause_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_intervention_pause_should_give_no_mod_key_error);
    RUN_TEST(test_prepare_intervention_pause_should_give_invalid_mod_value_error);
    RUN_TEST(test_prepare_intervention_pause_should_give_success);

    /***************** prepare intervention resume *******************/

    RUN_TEST(test_prepare_intervention_resume_should_give_no_spp_key_error);

    // resume pro
    RUN_TEST(test_prepare_intervention_resume_pro_should_give_success);

    // resume all
    RUN_TEST(test_prepare_intervention_resume_all_should_give_success);

    // resume individual
    RUN_TEST(test_prepare_intervention_resume_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_intervention_resume_should_give_no_mod_key_error);
    RUN_TEST(test_prepare_intervention_resume_should_give_invalid_mod_value_error);
    RUN_TEST(test_prepare_intervention_resume_should_give_success);

    /****************** prepare intervention stop ********************/

    RUN_TEST(test_prepare_intervention_stop_should_give_no_spp_key_error);

    // stop pro
    RUN_TEST(test_prepare_intervention_stop_pro_should_give_success);

    // stop all
    RUN_TEST(test_prepare_intervention_stop_all_should_give_success);

    // stop individual
    RUN_TEST(test_prepare_intervention_stop_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_intervention_stop_should_give_no_mod_key_error);
    RUN_TEST(test_prepare_intervention_stop_should_give_invalid_mod_value_error);
    RUN_TEST(test_prepare_intervention_stop_should_give_success);

    UNITY_END();
}

#endif // UNIT_TEST