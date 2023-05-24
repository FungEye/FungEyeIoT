#include "gtest/gtest.h"
#include "fff.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"

// Include interfaces and define global variables
// defined by the production code
extern "C"
{
	#include "LoRaWANHandler.h"
    #include "lora_driver.h"
}

// Create Fake functions
FAKE_VALUE_FUNC(uint8_t, lora_driver_getMaxPayloadSize);
FAKE_VOID_FUNC(lora_driver_initialise, serial_comPort_t, MessageBufferHandle_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setOtaaIdentity, char *, char *, char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_configureToEu868);
FAKE_VALUE_FUNC(char *, lora_driver_mapReturnCodeToText, lora_driver_returnCode_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setAbpIdentity, char *, char *, char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_join, lora_driver_joinMode_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_sendUploadMessage, bool, lora_driver_payload_t *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setDeviceIdentifier, const char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setApplicationIdentifier, const char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setApplicationKey, const char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setNetworkSessionKey, const char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setApplicationSessionKey, const char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setDeviceAddress, const char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setDataRate, uint8_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getDataRate, uint8_t *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setAdaptiveDataRate, lora_driver_adaptiveDataRate_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getAdaptiveDataRate, lora_driver_adaptiveDataRate_t *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setReceiveDelay, uint16_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setAutomaticReply, lora_driver_automaticReplyMode_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getAutomaticReply, lora_driver_automaticReplyMode_t *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setLinkCheckInterval, uint16_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getLinkCheckResult, uint8_t *, uint8_t *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setSpreadingFactor, uint8_t);
FAKE_VOID_FUNC(lora_driver_resetRn2483, uint8_t);
FAKE_VOID_FUNC(lora_driver_flushBuffers);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getRn2483Hweui, char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_rn2483GetVdd, char *);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_rn2483Reboot);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_rn2483FactoryReset);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_sleep, uint32_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_saveMac);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_pauseMac);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_resumeMac);

//Servo functions
FAKE_VOID_FUNC(rc_servo_initialise);
FAKE_VOID_FUNC(rc_servo_setPosition, uint8_t, int8_t);

//Servo functions defined in testForCO2

// Create Test fixture and Reset all Mocks before each test
class Test_production : public ::testing::Test
{
protected:
	void SetUp() override
	{
        RESET_FAKE(lora_driver_getMaxPayloadSize);
        RESET_FAKE(lora_driver_initialise);
        RESET_FAKE(lora_driver_setOtaaIdentity);
        RESET_FAKE(lora_driver_configureToEu868);
        RESET_FAKE(lora_driver_mapReturnCodeToText);
        RESET_FAKE(lora_driver_setAbpIdentity);
        RESET_FAKE(lora_driver_join);
        RESET_FAKE(lora_driver_sendUploadMessage);
        RESET_FAKE(lora_driver_setDeviceIdentifier);
        RESET_FAKE(lora_driver_setApplicationIdentifier);
        RESET_FAKE(lora_driver_setApplicationKey);
        RESET_FAKE(lora_driver_setNetworkSessionKey);
        RESET_FAKE(lora_driver_setApplicationSessionKey);
        RESET_FAKE(lora_driver_setDeviceAddress);
        RESET_FAKE(lora_driver_setDataRate);
        RESET_FAKE(lora_driver_getDataRate);
        RESET_FAKE(lora_driver_setAdaptiveDataRate);
        RESET_FAKE(lora_driver_getAdaptiveDataRate);
        RESET_FAKE(lora_driver_setReceiveDelay);
        RESET_FAKE(lora_driver_setAutomaticReply);
        RESET_FAKE(lora_driver_getAutomaticReply);
        RESET_FAKE(lora_driver_setLinkCheckInterval);
        RESET_FAKE(lora_driver_getLinkCheckResult);
        RESET_FAKE(lora_driver_setSpreadingFactor);
        RESET_FAKE(lora_driver_resetRn2483);
        RESET_FAKE(lora_driver_flushBuffers);
        RESET_FAKE(lora_driver_getRn2483Hweui);
        RESET_FAKE(lora_driver_rn2483GetVdd);
        RESET_FAKE(lora_driver_rn2483Reboot);
        RESET_FAKE(lora_driver_rn2483FactoryReset);
        RESET_FAKE(lora_driver_sleep);
        RESET_FAKE(lora_driver_saveMac);
        RESET_FAKE(lora_driver_pauseMac);
        RESET_FAKE(lora_driver_resumeMac);

       		//servo
		RESET_FAKE(rc_servo_initialise);
		RESET_FAKE(rc_servo_setPosition);

		RESET_FAKE(xTaskCreate);
		RESET_FAKE(xTaskGetTickCount);
		RESET_FAKE(xTaskDelayUntil);

		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

TEST_F(Test_production, lora_initialization) {
    //clearing call count
    xMessageBufferCreate_fake.call_count = 0;
    lora_driver_initialise_fake.call_count = 0;

    QueueHandle_t queue_Temp1 = xQueueCreate(1, sizeof(int));
    QueueHandle_t queue_Hum1= xQueueCreate(1, sizeof(int));
    QueueHandle_t queueCo2= xQueueCreate(1, sizeof(int));
    QueueHandle_t queue_Light1= xQueueCreate(1, sizeof(int));

    EventGroupHandle_t groupLora;
	groupLora = xEventGroupCreate();

    lora_initializer( queue_Temp1,  queue_Hum1,  queueCo2,  queue_Light1, groupLora);

    //checking if we create a buffer handling downlink
    ASSERT_EQ(xMessageBufferCreate_fake.call_count, 1);

    //checking if we initialize the driver
	ASSERT_EQ(lora_driver_initialise_fake.call_count, 1);
}

TEST_F(Test_production, lora_initializationTaskCreation) {

    //clearing call count
    xTaskCreate_fake.call_count = 0;

    //setup
    UBaseType_t lora_handler_task_priority = 1;

    //test
    lora_handler_initialise(lora_handler_task_priority);

    // is xTaskCreate called twice - 
    // one for uplink and one for downlink task
	ASSERT_EQ(xTaskCreate_fake.call_count, 2);
}

TEST_F(Test_production, lora_queuesSetup) {
        //clearing call count
    xQueueReceive_fake.call_count = 0;

    receive_from_queues();
    ASSERT_EQ(xQueueReceive_fake.call_count, 4);
}

TEST_F(Test_production, lora_queuesReset) {
        //clearing call count
    xQueueReset_fake.call_count = 0;

    reset_queues();
    ASSERT_EQ(xQueueReset_fake.call_count, 4);
}

TEST_F(Test_production, lora_handlerDownlink){
    xMessageBufferReceive_fake.call_count = 0;

   //setup
    MessageBufferHandle_t downLinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
    UBaseType_t lora_handler_task_priority = 1;

    //lora_handler_initialise(lora_handler_task_priority);
    getting_downlink();

    //correctly calling xMessageBufferReceive
    ASSERT_EQ(xMessageBufferReceive_fake.call_count, 1);
    ASSERT_EQ(xMessageBufferReceive_fake.arg0_val, downLinkMessageBufferHandle);
    ASSERT_EQ(xMessageBufferReceive_fake.arg2_val, sizeof(lora_driver_payload_t));
    ASSERT_EQ(xMessageBufferReceive_fake.arg3_val, portMAX_DELAY);
}


TEST_F(Test_production, lora_handlerDownlinkTask_servo_0) {
    //setup
   static int servoState = 1; 

    getting_downlink();
	
    ASSERT_EQ(rc_servo_setPosition_fake.arg0_val, 0);
    ASSERT_EQ(rc_servo_setPosition_fake.arg1_val, -100);

}

TEST_F(Test_production, lora_handlerDownlinkTask_servo_1) {
    //setup
   static int servoState = 0; 

    getting_downlink();
	
    ASSERT_EQ(rc_servo_setPosition_fake.arg0_val, 0);
    ASSERT_EQ(rc_servo_setPosition_fake.arg1_val, 100);

}
