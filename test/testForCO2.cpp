// #include "gtest/gtest.h"
// #include "fff.h"
// #include "FreeRTOS_FFF_MocksDeclaration.h"
// // Include interfaces and define global variables
// // defined by the production code
// extern "C"
// {
// 	#include "CO2.h"
// 	#include "mh_z19.h"
// }

// // Create Fake Driver functions
// FAKE_VOID_FUNC(mh_z19_initialise, serial_comPort_t);
// FAKE_VOID_FUNC(mh_z19_injectCallBack);
// FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);
// FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_getCo2Ppm, 	uint16_t *);
// FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_setAutoCalibration, bool);
// FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_calibrateZeroPoint);
// FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_calibrateSpanPoint, uint16_t);

// // Create Test fixture and Reset all Mocks before each test
// class Test_production : public ::testing::Test
// {
// protected:
// 	void SetUp() override
// 	{
// 		RESET_FAKE(xTaskCreate);
// 		RESET_FAKE(mh_z19_initialise);
// 		RESET_FAKE(mh_z19_injectCallBack);
// 		RESET_FAKE(mh_z19_takeMeassuring);
// 		RESET_FAKE(mh_z19_getCo2Ppm);
// 		RESET_FAKE(mh_z19_setAutoCalibration);
// 		RESET_FAKE(mh_z19_calibrateZeroPoint);
// 		RESET_FAKE(mh_z19_calibrateSpanPoint);
// 		RESET_FAKE(xTaskGetTickCount);
// 		RESET_FAKE(xTaskDelayUntil);
// 		FFF_RESET_HISTORY();
// 	}
// 	void TearDown() override
// 	{}
// };


// TEST_F(Test_production, co2xTaskCreateCalledOnce) {
	
// 	co2Task_create();
// 	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
// }

// // Test that the task is created correct
// TEST_F(Test_production, co2_taskCreateArgsCheck)
// {
// 	// Create the co2 task
// 	co2Task_create();

// 	// Is xTaskCreate called?
// 	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
// 	// Check all arguments to xTaskCreate
// 	ASSERT_EQ(xTaskCreate_fake.arg0_val, &_runCO2);
// 	ASSERT_EQ(strncmp(xTaskCreate_fake.arg1_val, "CO2", 8), 0);
// 	ASSERT_EQ(xTaskCreate_fake.arg2_val, configMINIMAL_STACK_SIZE);
// 	ASSERT_EQ(xTaskCreate_fake.arg3_val, nullptr);
// 	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
// 	ASSERT_EQ(xTaskCreate_fake.arg5_val, nullptr);

// }

// TEST_F(Test_production, co2_vTaskDelayCallArgs) {
	
// 	co2Task_create();
//     co2Task_run();

//     ASSERT_EQ(vTaskDelay_fake.arg0_val, pdMS_TO_TICKS(6000));
// }
