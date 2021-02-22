#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "device_manager.h"
#include "stepper/partial/stepper_calculator.h"

void setUp() // default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

/**************** linear stepper speed calculator ********************/

void test_linear_stepper_speed_calculator_1()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    Speed regs;

    regs = calculate_speed(stepper, 0.1);

    TEST_ASSERT_EQUAL_UINT16(39, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32767, regs.pul);
}

void test_linear_stepper_speed_calculator_2()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    Speed regs;

    regs = calculate_speed(stepper, 1);

    TEST_ASSERT_EQUAL_UINT16(4, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32767, regs.pul);
}

void test_linear_stepper_speed_calculator_3()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    Speed regs;

    regs = calculate_speed(stepper, 5);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(51670, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(25835, regs.pul);
}

void test_linear_stepper_speed_calculator_4()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    Speed regs;

    regs = calculate_speed(stepper, 10);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(25834, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(12917, regs.pul);
}

void test_linear_stepper_speed_calculator_5()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    Speed regs;

    regs = calculate_speed(stepper, 100);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(2583, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(1291, regs.pul);
}

/**************** linear stepper steps calculator ********************/

void test_linear_stepper_steps_calculator_1()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(0.01);

    TEST_ASSERT_EQUAL_UINT16(2, steps);
}

void test_linear_stepper_steps_calculator_2()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(0.1);

    TEST_ASSERT_EQUAL_UINT16(15, steps);
}

void test_linear_stepper_steps_calculator_3()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(1);

    TEST_ASSERT_EQUAL_UINT16(155, steps);
}

void test_linear_stepper_steps_calculator_4()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(10);

    TEST_ASSERT_EQUAL_UINT16(1548, steps);
}

void test_linear_stepper_steps_calculator_5()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(100);

    TEST_ASSERT_EQUAL_UINT16(15483, steps);
}

/**************** circular stepper speed calculator ********************/

void test_circular_stepper_speed_calculator_1()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"w");
    Speed regs;

    regs = calculate_speed(stepper, 1);

    TEST_ASSERT_EQUAL_UINT16(3, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32767, regs.pul);
}

void test_circular_stepper_speed_calculator_2()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"w");
    Speed regs;

    regs = calculate_speed(stepper, 5);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(39473, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(19736, regs.pul);
}

void test_circular_stepper_speed_calculator_3()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"w");
    Speed regs;

    regs = calculate_speed(stepper, 10);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(19736, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(9868, regs.pul);
}

void test_circular_stepper_speed_calculator_4()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"w");
    Speed regs;

    regs = calculate_speed(stepper, 100);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(1973, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(986, regs.pul);
}

/**************** circular stepper steps calculator ********************/

void test_circular_stepper_steps_calculator_1()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(0.1);

    TEST_ASSERT_EQUAL_UINT16(3, steps);
}

void test_circular_stepper_steps_calculator_2()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(1);

    TEST_ASSERT_EQUAL_UINT16(34, steps);
}

void test_circular_stepper_steps_calculator_3()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(10);

    TEST_ASSERT_EQUAL_UINT16(338, steps);
}

void test_circular_stepper_steps_calculator_4()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(100);

    TEST_ASSERT_EQUAL_UINT16(3378, steps);
}

void test_circular_stepper_steps_calculator_5()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");

    uint8_t steps = calculate_steps(360);

    TEST_ASSERT_EQUAL_UINT16(12160, steps);
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    // linear stepper speed calculator
    RUN_TEST(test_linear_stepper_speed_calculator_1);
    RUN_TEST(test_linear_stepper_speed_ccalculator_2);
    RUN_TEST(test_linear_stepper_speed_ccalculator_3);
    RUN_TEST(test_linear_stepper_speed_ccalculator_4);
    RUN_TEST(test_linear_stepper_speed_ccalculator_5);

    // linear stepper steps calculator
    RUN_TEST(test_linear_stepper_steps_calculator_1);
    RUN_TEST(test_linear_stepper_steps_calculator_2);
    RUN_TEST(test_linear_stepper_steps_calculator_3);
    RUN_TEST(test_linear_stepper_steps_calculator_4);
    RUN_TEST(test_linear_stepper_steps_calculator_5);

    // circular stepper speed calculator
    RUN_TEST(test_circular_stepper_speed_calculator_1);
    RUN_TEST(test_circular_stepper_speed_calculator_2);
    RUN_TEST(test_circular_stepper_speed_calculator_3);
    RUN_TEST(test_circular_stepper_speed_calculator_4);
    RUN_TEST(test_circular_stepper_speed_calculator_5);

    // circular stepper steps calculator
    RUN_TEST(test_circular_stepper_steps_calculator_1);
    RUN_TEST(test_circular_stepper_steps_calculator_2);
    RUN_TEST(test_circular_stepper_steps_calculator_3);
    RUN_TEST(test_circular_stepper_steps_calculator_4);
    RUN_TEST(test_circular_stepper_steps_calculator_5);

    UNITY_END();
}

#endif // UNIT_TEST