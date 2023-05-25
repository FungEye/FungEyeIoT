/**
 * @file LoRaWANHandler.c
 * @brief Source file for all lora related commuications
 */

#include "../headerFiles/LoRaWANHandler.h"
//#include <task.h> // just added

void lora_handler_task( void *pvParameters );
void lora_downlink_task(void *pvParameters);

//Event groups
EventGroupHandle_t _measuredEventGroupLora;

static lora_driver_payload_t _uplink_payload;

//Queues
QueueHandle_t queue_Temp;
QueueHandle_t queue_Hum;
QueueHandle_t queue_CO2; 
QueueHandle_t queue_Light;

//local variables
static int16_t hum;	// measured hum
static int16_t temp; // measured temp
static int16_t co2; // measured CO2
static int16_t lux;	// measured lux
static int servoState = 0; // 1 indicates that the servo is in the opening position and 0 that it is in the closing position

MessageBufferHandle_t downLinkMessageBufferHandle; // Here I make room for two downlink messages in the message buffer

void lora_initializer(QueueHandle_t queue_Temp1, QueueHandle_t queue_Hum1, QueueHandle_t queueCo2, QueueHandle_t queue_Light1, EventGroupHandle_t measuredEventGroup){
	_measuredEventGroupLora = measuredEventGroup;
	queue_Temp = queue_Temp1;
	queue_Hum = queue_Hum1;
	queue_CO2 = queueCo2;
	queue_Light = queue_Light1;

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
		// Connected to LoRaWAN
	}
	else
	{
		// Something went wrong
		printf("Did not connect to LoRaWAN. Check the issue.");
		// Lets stay here
		while (1)
		{
		}
	}
}

/*-----------------------------------------------------------*/
void lora_handler_task( void *pvParameters )
{
	lora_uplink_setup();

	_uplink_payload.len = 8;
	_uplink_payload.portNo = 2;
	
	for(;;)
	{
		vTaskDelay(pdMS_TO_TICKS(300000)); // Upload message every 5 minutes (300000 ms)
		
		puts("\n-----Waiting for bits.-----\n");

		xEventGroupWaitBits(_measuredEventGroupLora,
			BIT_TASK_TEMP_READY | BIT_TASK_HUM_READY | BIT_TASK_CO2_READY | BIT_TASK_LIGHT_READY,
			pdTRUE,
			pdTRUE,
			portMAX_DELAY);
			
			
		puts("\n-----All bits are set.-----\n");
		
		setting_payload();
		reset_queues();
		printf("Upload Message >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_sendUploadMessage(false, &_uplink_payload)));
		
	}
}

void lora_uplink_setup(){
	// Hardware reset of LoRaWAN transceiver
	lora_driver_resetRn2483(1);
	vTaskDelay(2);
	lora_driver_resetRn2483(0);
	// Give it a chance to wakeup
	vTaskDelay(150);

	lora_driver_flushBuffers(); // get rid of first version string from module after reset!

	_lora_setup();
}

void receive_from_queues(){
	xQueueReceive( queue_Hum,
                    &( hum ),
                    ( TickType_t ) 20 );

	xQueueReceive( queue_Temp,
                    &( temp ),
                    ( TickType_t ) 20 );

	vTaskDelay(pdMS_TO_TICKS(3000));
	xQueueReceive( queue_CO2,
                    &( co2 ),
                    ( TickType_t ) 20 );
	
	xQueueReceive( queue_Light,
                    &( lux ),
                    ( TickType_t ) 20 );
}

void reset_queues(){
	xQueueReset(queue_Hum);
	xQueueReset(queue_Temp);
	xQueueReset(queue_Light);
	xQueueReset(queue_CO2);
}

void setting_payload(){
		receive_from_queues();
		
		printf("TEMP BEFORE SEND: %d\n",temp);
		printf("HUMID BEFORE SEND: %d\n",hum);
		printf("CO2 BEFORE SEND: %d\n",co2);
		printf("LUX BEFORE SEND: %d\n",lux);

		_uplink_payload.bytes[0] = hum >> 8;
		_uplink_payload.bytes[1] = hum & 0xFF;
		_uplink_payload.bytes[2] = temp >> 8;
		_uplink_payload.bytes[3] = temp & 0xFF;
		_uplink_payload.bytes[4] = co2 >> 8;
		_uplink_payload.bytes[5] = co2 & 0xFF;
		_uplink_payload.bytes[6] = lux >> 8;
		_uplink_payload.bytes[7] = lux & 0xFF;
}

/*-----------------------------------------------------------*/
void lora_downlink_task( void *pvParameters )
{
	lora_downlink_setup();
	
	for(;;){
		getting_downlink();
	}
}

void lora_downlink_setup(){
	// Hardware reset of LoRaWAN transceiver
	lora_driver_resetRn2483(1);
	vTaskDelay(2);
	lora_driver_resetRn2483(0);
	// Give it a chance to wakeup
	vTaskDelay(150);

	lora_driver_flushBuffers(); // get rid of first version string from module after reset!
}

void getting_downlink(){
		lora_driver_payload_t downlinkPayload;

		// this code must be in the loop of a FreeRTOS task!
		xMessageBufferReceive(downLinkMessageBufferHandle, &downlinkPayload, sizeof(lora_driver_payload_t), portMAX_DELAY);
		
		printf("\nDOWN LINK: from port: %d with payload %d \n", downlinkPayload.portNo, downlinkPayload.bytes[0]); // Just for Debug
			
		if (servoState == 1) // Check that we have got the expected 4 bytes
		{
			servo_close();
			servoState = 0;
			printf("Closing servo !!!\n");
		}
		else if(servoState == 0){
			servo_open();
			servoState = 1;
			printf("Opening servo !!!\n");
		}
		else{
			printf("SERVO UNKNOWN VALUE\n");
		}
}


