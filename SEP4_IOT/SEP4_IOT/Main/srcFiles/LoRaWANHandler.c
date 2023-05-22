/**
 * @file LoRaWANHandler.c
 * @brief Source file for all lora related commuications
 */

#include "../headerFiles/LoRaWANHandler.h"
//#include <task.h> // just added

void lora_handler_task( void *pvParameters );
void lora_downlink_task(void *pvParameters);

//Event groups
EventGroupHandle_t _measuredEventGroup;

static lora_driver_payload_t _uplink_payload;
extern int16_t temperature;
extern int16_t humidity;
extern int16_t co2;
extern int16_t luxInInt;

MessageBufferHandle_t downLinkMessageBufferHandle; // Here I make room for two downlink messages in the message buffer

void lora_initializer(){
	downLinkMessageBufferHandle  = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
	lora_driver_initialise(ser_USART1, downLinkMessageBufferHandle); // The parameter is the USART port the RN2483 module is connected to - in this case USART1 - here no message buffer for down-link messages are defined
}

void lora_handler_initialise(UBaseType_t lora_handler_task_priority)
{	
	xTaskCreate(
	lora_handler_task
	,  "LRHand"  // A name just for humans
	,  configMINIMAL_STACK_SIZE+200  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  lora_handler_task_priority  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
	
	xTaskCreate(
	lora_downlink_task
	,  "Downlink"  // A name just for humans
	,  configMINIMAL_STACK_SIZE+200  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  lora_handler_task_priority  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

static void _lora_setup(void)
{
	char _out_buf[20];
	lora_driver_returnCode_t rc;

	// Factory reset the transceiver
	printf("FactoryReset >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_rn2483FactoryReset()));
	
	// Configure to EU868 LoRaWAN standards
	printf("Configure to EU868 >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_configureToEu868()));

	// Get the transceivers HW EUI
	rc = lora_driver_getRn2483Hweui(_out_buf);
	printf("Get HWEUI >%s<: %s\n",lora_driver_mapReturnCodeToText(rc), _out_buf);

	// Set the HWEUI as DevEUI in the LoRaWAN software stack in the transceiver
	printf("Set DevEUI: %s >%s<\n", _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setDeviceIdentifier(_out_buf)));

	// Set Over The Air Activation parameters to be ready to join the LoRaWAN
	printf("Set OTAA Identity appEUI:%s appKEY:%s devEUI:%s >%s<\n", LORA_appEUI, LORA_appKEY, _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setOtaaIdentity(LORA_appEUI,LORA_appKEY,_out_buf)));

	// Save all the MAC settings in the transceiver
	printf("Save mac >%s<\n",lora_driver_mapReturnCodeToText(lora_driver_saveMac()));

	// Enable Adaptive Data Rate
	printf("Set Adaptive Data Rate: ON >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_setAdaptiveDataRate(LORA_ON)));

	// Set receiver window1 delay to 500 ms - this is needed if down-link messages will be used
	printf("Set Receiver Delay: %d ms >%s<\n", 500, lora_driver_mapReturnCodeToText(lora_driver_setReceiveDelay(500)));

	// Join the LoRaWAN
	uint8_t maxJoinTriesLeft = 10;
	
	do {
		rc = lora_driver_join(LORA_OTAA);
		printf("Join Network TriesLeft:%d >%s<\n", maxJoinTriesLeft, lora_driver_mapReturnCodeToText(rc));

		if ( rc != LORA_ACCEPTED)
		{
			vTaskDelay(pdMS_TO_TICKS(5000UL));
		}
		else
		{
			break;
		}
	} while (--maxJoinTriesLeft);

	if (rc == LORA_ACCEPTED)
	{
		// Connected to LoRaWAN :-)
	}
	else
	{
		// Something went wrong
		// Lets stay here
		while (1)
		{
		}
	}
}

/*-----------------------------------------------------------*/
void lora_handler_task( void *pvParameters )
{
	// Hardware reset of LoRaWAN transceiver
	lora_driver_resetRn2483(1);
	vTaskDelay(2);
	lora_driver_resetRn2483(0);
	// Give it a chance to wakeup
	vTaskDelay(150);

	lora_driver_flushBuffers(); // get rid of first version string from module after reset!

	_lora_setup();

	_uplink_payload.len = 8;
	_uplink_payload.portNo = 2;

	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(100000UL); // Upload message every 5 minutes (300000 ms)
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		xEventGroupWaitBits(_measuredEventGroup,
			BIT_TASK_TEMP_READY | BIT_TASK_CO2_READY | BIT_TASK_LIGHT_READY,
			pdTRUE,
			pdTRUE,
			portMAX_DELAY);
			
		puts("All bits are set, measurement is ready");
		
		setting_payload();
		printf("Upload Message >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_sendUploadMessage(false, &_uplink_payload)));
	}
}

void setting_payload(){
		// Some dummy payload
		uint16_t hum = humidity; // measured humidity
		int16_t temp = temperature; // measured temp
		uint16_t co2_ppm = co2; // measured CO2
		uint16_t lux = luxInInt;
		
		printf("TEMP BEFORE SEND: %d\n",temperature);
		printf("HUMID BEFORE SEND: %d\n",humidity);
		printf("CO2 BEFORE SEND: %d\n",co2_ppm);
		printf("LUX BEFORE SEND: %d\n",lux);

		_uplink_payload.bytes[0] = hum >> 8;
		_uplink_payload.bytes[1] = hum & 0xFF;
		_uplink_payload.bytes[2] = temp >> 8;
		_uplink_payload.bytes[3] = temp & 0xFF;
		_uplink_payload.bytes[4] = co2_ppm >> 8;
		_uplink_payload.bytes[5] = co2_ppm & 0xFF;
		_uplink_payload.bytes[6] = lux >> 8;
		_uplink_payload.bytes[7] = lux & 0xFF;
}

/*-----------------------------------------------------------*/
void lora_downlink_task( void *pvParameters )
{
	// Hardware reset of LoRaWAN transceiver
	lora_driver_resetRn2483(1);
	vTaskDelay(2);
	lora_driver_resetRn2483(0);
	// Give it a chance to wakeup
	vTaskDelay(150);

	lora_driver_flushBuffers(); // get rid of first version string from module after reset!

	
	for(;;){
		lora_driver_payload_t downlinkPayload;
		
		// this code must be in the loop of a FreeRTOS task!
		xMessageBufferReceive(downLinkMessageBufferHandle, &downlinkPayload, sizeof(lora_driver_payload_t), portMAX_DELAY);
		
		printf("DOWN LINK: from port: %d with payload %d \n", downlinkPayload.portNo, downlinkPayload.bytes[0]); // Just for Debug
			
		if (0 == downlinkPayload.bytes[0]) // Check that we have got the expected 4 bytes
		{
			servo_close();
			printf("Closing servo !!!\n");
		}
		else if(1 == downlinkPayload.bytes[0]){
			servo_open();
			
			printf("Opening servo !!!\n");
		}
		else{
			printf("SERVO UNKNOWN VALUE\n");
		}
	}
}
