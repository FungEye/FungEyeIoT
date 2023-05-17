#include "gtest/gtest.h"
#include "fff.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
// Include interfaces and define global variables
// defined by the production code
extern "C"
{
	#include "CO2.h"
	#include "mh_z19.h"
}

// Additional type needed to be able to use callback in fff 
typedef void (*my_callback)(uint16_t);

// Create Fake Driver functions
FAKE_VOID_FUNC(mh_z19_initialise, serial_comPort_t);
FAKE_VOID_FUNC(mh_z19_injectCallBack, my_callback);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_getCo2Ppm, 	uint16_t *);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_setAutoCalibration, bool);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_calibrateZeroPoint);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_calibrateSpanPoint, uint16_t);

// Create Test fixture and Reset all Mocks before each test
class Test_production : public ::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(mh_z19_initialise);
		RESET_FAKE(mh_z19_injectCallBack);
		RESET_FAKE(mh_z19_takeMeassuring);
		RESET_FAKE(mh_z19_getCo2Ppm);
		RESET_FAKE(mh_z19_setAutoCalibration);
		RESET_FAKE(mh_z19_calibrateZeroPoint);
		RESET_FAKE(mh_z19_calibrateSpanPoint);
		RESET_FAKE(xTaskGetTickCount);
		RESET_FAKE(xTaskDelayUntil);
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

TEST_F(Test_production, co2_initialization) {

	initialize_CO2();
    
	ASSERT_EQ(mh_z19_initialise_fake.call_count, 1);
}


TEST_F(Test_production, co2_xTaskCreateCalledOnce) {
	
	co2Task_create();
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
}

// Test that the task is created correct
TEST_F(Test_production, co2_taskCreateArgsCheck)
{
	// Create the co2 task
	co2Task_create();

	// Is xTaskCreate called?
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	// Check all arguments to xTaskCreate
	ASSERT_EQ(xTaskCreate_fake.arg0_val, &_runCO2);
	ASSERT_EQ(strncmp(xTaskCreate_fake.arg1_val, "CO2", 8), 0);
	ASSERT_EQ(xTaskCreate_fake.arg2_val, configMINIMAL_STACK_SIZE);
	ASSERT_EQ(xTaskCreate_fake.arg3_val, nullptr);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
	ASSERT_EQ(xTaskCreate_fake.arg5_val, nullptr);

}

TEST_F(Test_production, co2_vTaskDelayCallArgs) {
	
	co2Task_create();
    co2Task_run();

    ASSERT_EQ(vTaskDelay_fake.arg0_val, pdMS_TO_TICKS(6000));
}

TEST_F(Test_production, co2_semaphoreCall){
	//Set up
	SemaphoreHandle_t semaphoreLight;
	semaphoreLight = xSemaphoreCreateBinary();
    xSemaphoreGive(semaphoreLight);

	//clearing the call count before calling the function
	xSemaphoreTake_fake.call_count = 0;
	xSemaphoreGive_fake.call_count = 0;

	co2Task_create();
	co2Task_run();

	ASSERT_EQ(xSemaphoreTake_fake.call_count, 1);
	ASSERT_EQ(xSemaphoreTake_fake.arg0_val, semaphoreLight);
	ASSERT_EQ(xSemaphoreTake_fake.arg1_val, portMAX_DELAY);
	ASSERT_EQ(xSemaphoreGive_fake.call_count, 1);
}

// TEST_F(Test_production, co2_measurement) {
// 	//setup
// 	mh_z19_returnCode_t rc = MHZ19_OK;
// 	mh_z19_takeMeassuring_fake.return_val = rc;
	
// 	co2Task_create();
//     co2Task_run();

//     ASSERT_EQ(vTaskDelay_fake.arg0_val, pdMS_TO_TICKS(6000));
// }
