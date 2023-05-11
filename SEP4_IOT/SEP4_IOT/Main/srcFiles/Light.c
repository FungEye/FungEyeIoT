/*
 * Light.c
 *
 * Created: 10/05/2023 10:43:00
 *  Author: ninaw
 */ 

#include "../headerFiles/Light.h"

float luxValue;
int16_t luxInInt;
uint16_t fullRaw;
uint16_t visibleRaw;
uint16_t infraredRaw;

// Callback function for TSL2591 driver
void tsl2591Callback(tsl2591_returnCode_t rc)
{
	uint16_t tmp;

	switch (rc)
	{
		case TSL2591_DATA_READY:
		
		if (TSL2591_OK == tsl2591_getLux(&luxValue))
		{
			luxInInt = (int16_t)luxValue;
			char luxString[16];
			sprintf(luxString, "Lux: %d", luxInInt);
			puts(luxString);
			vTaskDelay(pdMS_TO_TICKS(6000));
		}
		break;

		case TSL2591_OK:
			// Last command performed successfully
			break;

		case TSL2591_DEV_ID_READY:
			// Dev ID now fetched
			break;

		default:
			break;
	}
}

void initialize_Light()
{
	if (TSL2591_OK == tsl2591_initialise(tsl2591Callback))
	{
		// Driver initialized successfully
		// Always check what tsl2591_initialise() returns
	}
}

void lightTask_run()
{
	if (TSL2591_OK == tsl2591_enable())
	{
		// The power-up command is now sent to the sensor
		// It can be powered down with a call to tsl2591_disable()
	}

	if (TSL2591_OK != tsl2591_fetchData())
	{
		// Something went wrong
		// Investigate the return code further
	}
	else
	{
		// The light data will be ready after the driver calls the callback function with TSL2591_DATA_READY.
	}
}

void lightTask_create()
{
	xTaskCreate(
		_runLight,				       // Name of method
		"Light",						   // A name just for humans
		configMINIMAL_STACK_SIZE,	   // This stack size can be checked & adjusted by reading the Stack Highwater
		NULL,					   	   // (void *pvParameters)
		1,							   // the priority of the task
		NULL						  
// No TaskHandle created.
);
}

void _runLight(void* params)
{
	// In the future, we could use this for some INIT values
	while (1) {
		lightTask_run();
	}
}