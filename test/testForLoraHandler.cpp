#include "gtest/gtest.h"
#include "fff.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
// Include interfaces and define global variables
// defined by the production code
extern "C"
{
	#include "LoRaWANHandler.h"
    #include "lora_driver.h"
    #include "rc_servo.h"

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

		RESET_FAKE(xTaskCreate);
		RESET_FAKE(xTaskGetTickCount);
		RESET_FAKE(xTaskDelayUntil);
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

TEST_F(Test_production, lora_initialization) {
	ASSERT_EQ(1, 1);
}