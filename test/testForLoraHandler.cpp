// #include "gtest/gtest.h"
// #include "fff.h"
// #include "FreeRTOS_FFF_MocksDeclaration.h"
// // Include interfaces and define global variables
// // defined by the production code
// extern "C"
// {
// 	#include "LoRaWANHandler.h"
//     #include "lora_driver.h"
// }

// // Create Fake functions
// FAKE_VALUE_FUNC(uint8_t, lora_driver_getMaxPayloadSize);
// FAKE_VOID_FUNC(lora_driver_initialise, serial_comPort_t, MessageBufferHandle_t);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setOtaaIdentity, char, char, char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_configureToEu868);
// FAKE_VALUE_FUNC(char *, lora_driver_mapReturnCodeToText, lora_driver_returnCode_t);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setAbpIdentity, char, char, char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_join, lora_driver_joinMode_t);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_sendUploadMessage, bool, lora_driver_payload_t *);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setDeviceIdentifier, const char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setApplicationIdentifier);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setApplicationKey, const char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setNetworkSessionKey, const char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setApplicationSessionKey, const char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setDeviceAddress, const char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setDataRate, uint8_t);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getDataRate, uint8_t *);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setAdaptiveDataRate, lora_driver_adaptiveDataRate_t);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getAdaptiveDataRate, lora_driver_adaptiveDataRate_t *);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setReceiveDelay, uint16_t);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setAutomaticReply, lora_driver_automaticReplyMode_t);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getAutomaticReply, lora_driver_automaticReplyMode_t *);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setLinkCheckInterval, uint16_t);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getLinkCheckResult, uint8_t *);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setSpreadingFactor, uint8_t);
// FAKE_VOID_FUNC(lora_driver_resetRn2483, uint8_t);
// FAKE_VOID_FUNC(lora_driver_flushBuffers);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getRn2483Hweui, char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_rn2483GetVdd, char);
// FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_rn2483Reboot);


// // Create Test fixture and Reset all Mocks before each test
// class Test_production : public ::testing::Test
// {
// protected:
// 	void SetUp() override
// 	{
// 		RESET_FAKE(xTaskCreate);
// 		RESET_FAKE(xTaskGetTickCount);
// 		RESET_FAKE(xTaskDelayUntil);
// 		FFF_RESET_HISTORY();
// 	}
// 	void TearDown() override
// 	{}
// };



