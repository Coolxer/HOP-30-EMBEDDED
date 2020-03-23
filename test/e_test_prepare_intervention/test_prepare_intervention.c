#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function


/*********************** prepare_intervention pause ***************************************/

// common
void test_prepare_intervention_pause_should_give_8()
{
    uint8_t data[] = "idx=1|opt=pau|abc=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=8|\n", connector_manage(connector_parse(data)));
}

// pause pro
void test_prepare_intervention_pause_pro_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=pau|spp=pro|mod=0|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

// pause all
void test_prepare_intervention_pause_all_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=pau|spp=all|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

// pause individual
void test_prepare_intervention_pause_should_give_9()
{
    uint8_t data[] = "idx=1|opt=pau|spp=a|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=9|\n", connector_manage(connector_parse(data)));
}

void test_prepare_intervention_pause_should_give_18()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = PAUSED;

    uint8_t data[] = "idx=1|opt=pau|spp=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=18|\n", connector_manage(connector_parse(data)));
}

void test_prepare_intervention_pause_should_give_finished()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = HOMING;

    uint8_t data[] = "idx=1|opt=pau|spp=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

/*********************** prepare_intervention resume ***************************************/

// common
void test_prepare_intervention_resume_should_give_8()
{
    uint8_t data[] = "idx=1|opt=res|abc=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=8|\n", connector_manage(connector_parse(data)));
}

// resume pro
void test_prepare_intervention_resume_pro_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=res|spp=pro|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

// resume all
void test_prepare_intervention_resume_all_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=res|spp=all|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

// resume individual
void test_prepare_intervention_resume_should_give_9()
{
    uint8_t data[] = "idx=1|opt=res|spp=a|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=9|\n", connector_manage(connector_parse(data)));
}

void test_prepare_intervention_resume_should_give_18()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = OFF;

    uint8_t data[] = "idx=1|opt=pau|spp=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=18|\n", connector_manage(connector_parse(data)));
}

void test_prepare_intervention_resume_should_give_finished()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = PAUSED;

    uint8_t data[] = "idx=1|opt=res|spp=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

/*********************** prepare_intervention stop ***************************************/

// common
void test_prepare_intervention_stop_should_give_8()
{
    uint8_t data[] = "idx=1|opt=sto|abc=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=8|\n", connector_manage(connector_parse(data)));
}

// stop pro
void test_prepare_intervention_stop_pro_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=sto|spp=pro|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

// stop all
void test_prepare_intervention_stop_all_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=sto|spp=all|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

// stop individual

void test_prepare_intervention_stop_should_give_9()
{
    uint8_t data[] = "idx=1|opt=sto|spp=a|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=9|\n", connector_manage(connector_parse(data)));
}

void test_prepare_intervention_stop_should_give_18()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = OFF;

    uint8_t data[] = "idx=1|opt=pau|spp=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=18|\n", connector_manage(connector_parse(data)));
}

void test_prepare_intervention_stop_should_give_finished()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = HOMING;

    uint8_t data[] = "idx=1|opt=sto|spp=x|mod=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    /***************** prepare intervention pause ********************/

    RUN_TEST(test_prepare_intervention_pause_should_give_8);

    // pause pro
    RUN_TEST(test_prepare_intervention_pause_pro_should_give_finished);

    // pause all
    RUN_TEST(test_prepare_intervention_pause_all_should_give_finished);

    // pause individual
    RUN_TEST(test_prepare_intervention_pause_should_give_9);
    RUN_TEST(test_prepare_intervention_pause_should_give_18);
    RUN_TEST(test_prepare_intervention_pause_should_give_finished);

    /***************** prepare intervention resume *******************/

    RUN_TEST(test_prepare_intervention_resume_should_give_8);

    // resume pro
    RUN_TEST(test_prepare_intervention_resume_pro_should_give_finished);

    // resume all
    RUN_TEST(test_prepare_intervention_resume_all_should_give_finished);

    // resume individual
    RUN_TEST(test_prepare_intervention_resume_should_give_9);
    RUN_TEST(test_prepare_intervention_resume_should_give_18);
    RUN_TEST(test_prepare_intervention_resume_should_give_finished);

    /****************** prepare intervention stop ********************/

    RUN_TEST(test_prepare_intervention_stop_should_give_8);

    // stop pro
    RUN_TEST(test_prepare_intervention_stop_pro_should_give_finished);

    // stop all
    RUN_TEST(test_prepare_intervention_stop_all_should_give_finished);

    // stop individual
    RUN_TEST(test_prepare_intervention_stop_should_give_9);
    RUN_TEST(test_prepare_intervention_stop_should_give_18);
    RUN_TEST(test_prepare_intervention_stop_should_give_finished);

    UNITY_END();
}

#endif // UNIT_TEST