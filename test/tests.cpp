#include "gtest/gtest.h"
#include "fff.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
// Include interfaces and define global variables
// defined by the production code
extern "C"
{
	#include "HumidityTemperature.h"
	#include "hih8120.h"
}

// Create Fake Driver functions
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_destroy);
FAKE_VALUE_FUNC(bool, hih8120_isReady);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);
FAKE_VALUE_FUNC(float, hih8120_getHumidity);
FAKE_VALUE_FUNC(float, hih8120_getTemperature);
//FAKE_VOID_FUNC(_run, void*);

// Create Test fixture and Reset all Mocks before each test
class Test_production : public ::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(hih8120_initialise);
		RESET_FAKE(hih8120_destroy);
		RESET_FAKE(hih8120_isReady);
		RESET_FAKE(hih8120_wakeup);
		RESET_FAKE(hih8120_measure);
		RESET_FAKE(hih8120_getHumidityPercent_x10);
		RESET_FAKE(hih8120_getTemperature_x10);
		RESET_FAKE(hih8120_getHumidity);
		RESET_FAKE(hih8120_getTemperature);
		RESET_FAKE(xTaskGetTickCount);
		RESET_FAKE(xTaskDelayUntil);
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

TEST_F(Test_production, humAndTemp_xTaskCreateCalledOnce) {
	
	humidityTemperatureTask_create();
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
}

// Test that the task is created correct
TEST_F(Test_production, humAndTemp_createTaskArgsCheck)
{
	// Create the co2 task
	humidityTemperatureTask_create();

	// Is xTaskCreate called?
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	// Check all arguments to xTaskCreate
	ASSERT_EQ(xTaskCreate_fake.arg0_val, &_run);
	ASSERT_EQ(strncmp(xTaskCreate_fake.arg1_val, "HumidityTemperature", 8), 0);
	ASSERT_EQ(xTaskCreate_fake.arg2_val, configMINIMAL_STACK_SIZE);
	ASSERT_EQ(xTaskCreate_fake.arg3_val, nullptr);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
	ASSERT_EQ(xTaskCreate_fake.arg5_val, nullptr);

}

TEST_F(Test_production, humAndTemp_vTaskDelayCallArgs) {
	humidityTemperatureTask_create();
	humidityTemperatureTask_run();

	ASSERT_EQ(vTaskDelay_fake.arg0_val, pdMS_TO_TICKS(6000));
}

