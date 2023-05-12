// #include "gtest/gtest.h"
// #include "fff.h"
// #include "FreeRTOS_FFF_MocksDeclaration.h"
// // Include interfaces and define global variables
// // defined by the production code
// extern "C"
// {
// 	#include "Light.h"
// 	#include "tsl2591.h"
// }

// // Create Fake Driver functions

// //cannot convert from 'overloaded-function' to 'fff_function_t'
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_initialise, tsl2591_returnCode_t);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_destroy);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_enable);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_disable);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_fetchDeviceId);
// FAKE_VALUE_FUNC(uint8_t, tsl2591_getDeviceId);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_setGainAndIntegrationTime, tsl2591_gain_t, tsl2591_integrationTime_t);
// FAKE_VALUE_FUNC(tsl2591_gain_t, tsl2591_getGain);
// FAKE_VALUE_FUNC(tsl2591_integrationTime_t, tsl2591_getIntegrationTime);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_fetchData);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl259_getVisibleRaw, uint16_t*);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_getInfraredRaw, uint16_t*);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_getFullSpectrumRaw, uint16_t*);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_getCombinedDataRaw, tsl2591_combinedData_t*);
// FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_getLux, float*);


// // Create Test fixture and Reset all Mocks before each test
// class Test_production : public ::testing::Test
// {
// protected:
// 	void SetUp() override
// 	{
// 		RESET_FAKE(xTaskCreate);
// 		RESET_FAKE(tsl2591_initialise);
// 		RESET_FAKE(tsl2591_destroy);
// 		RESET_FAKE(tsl2591_enable);
// 		RESET_FAKE(tsl2591_disable);
// 		RESET_FAKE(tsl2591_fetchDeviceId);
// 		RESET_FAKE(tsl2591_getDeviceId);
// 		RESET_FAKE(tsl2591_setGainAndIntegrationTime);
// 		RESET_FAKE(tsl2591_getGain);
// 		RESET_FAKE(tsl2591_getIntegrationTime);
//         RESET_FAKE(tsl2591_fetchData);
//         RESET_FAKE(tsl259_getVisibleRaw);
//         RESET_FAKE(tsl2591_getInfraredRaw);
//         RESET_FAKE(tsl2591_getFullSpectrumRaw);
//         RESET_FAKE(tsl2591_getCombinedDataRaw);
//         RESET_FAKE(tsl2591_getLux);
// 		RESET_FAKE(xTaskGetTickCount);
// 		RESET_FAKE(xTaskDelayUntil);
// 		FFF_RESET_HISTORY();
// 	}
// 	void TearDown() override
// 	{}
// };

// // TEST_F(Test_production, light_sensorInit) {
	
// // 	initialize_Light();
// // 	ASSERT_EQ(tsl2591_initialise.call_count, 1);
// // }

// TEST_F(Test_production, light_xTaskCreateCalledOnce) {
	
// 	lightTask_create();
// 	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
// }

// // Test that the task is created correct
// TEST_F(Test_production, light_createTaskArgsCheck)
// {
// 	// Create the co2 task
// 	lightTask_create();

// 	// Is xTaskCreate called?
// 	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
// 	// Check all arguments to xTaskCreate
// 	ASSERT_EQ(xTaskCreate_fake.arg0_val, &_runLight);
// 	ASSERT_EQ(strncmp(xTaskCreate_fake.arg1_val, "Light", 8), 0);
// 	ASSERT_EQ(xTaskCreate_fake.arg2_val, configMINIMAL_STACK_SIZE);
// 	ASSERT_EQ(xTaskCreate_fake.arg3_val, nullptr);
// 	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
// 	ASSERT_EQ(xTaskCreate_fake.arg5_val, nullptr);

// }

// TEST_F(Test_production, humAndTemp_vTaskDelayCallArgs) {
// 	lightTask_create();
// 	lightTask_run();

// 	ASSERT_EQ(vTaskDelay_fake.arg0_val, pdMS_TO_TICKS(6000));
// }

