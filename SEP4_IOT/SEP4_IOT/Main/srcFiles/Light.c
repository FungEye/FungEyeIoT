/*
 * Light.c
 *
 * Created: 10/05/2023 10:43:00
 *  Author: ninaw
 */ 

#include "../headerFiles/Light.h"

float luxValue;
int16_t luxInInt;

// Callback function for TSL2591 driver
void tsl2591Callback(tsl2591_returnCode_t rc)
{
		vTaskDelay(pdMS_TO_TICKS(6000));
		switch (rc)
		{
			case TSL2591_DATA_READY:
			/*
			if (TSL2591_OK == tsl2591_getFullSpectrumRaw(&fullRaw))
			{
				// Full spectrum raw data available, use 'fullRaw' variable
			}

			if (TSL2591_OK == tsl259_getVisibleRaw(&visibleRaw))
			{
				// Visible raw data available, use 'visibleRaw' variable
			}

			if (TSL2591_OK == tsl2591_getInfraredRaw(&infraredRaw))
			{
				// Infrared raw data available, use 'infraredRaw' variable
			}
			*/

			if (TSL2591_OK == tsl2591_getLux(&luxValue))
			{
				luxInInt= (int16_t)luxValue;
				printf("Lux:%d\n", luxInInt);
			}
			break;

			// Handle other return codes if needed
		}
}
	
void initialize_Light(){
	tsl2591_initialise(tsl2591Callback);
}


void lightTask_run(){
	if ( TSL2591_OK == tsl2591_enable() )
	{
	}
	
	// The power up command is now send to the sensor - it can be powered down with a call to tsl2591_disable()
		if ( TSL2591_OK != tsl2591_fetchData() )
		{
			// Something went wrong
			// Investigate the return code further
		}
		else
		{
			//The light data will be ready after the driver calls the call back function with TSL2591_DATA_READY.
		}
	
	//tsl2591_disable();

	
}


void lightTask_create(){
	xTaskCreate(
	_runLight,				       // Name of method
	"Light",						   // A name just for humans
	configMINIMAL_STACK_SIZE,	   // This stack size can be checked & adjusted by reading the Stack Highwater
	NULL,					   	   // (void *pvParameters)
	1,							   //the priority of the task
	NULL							   //No TaskHandle created.
	);
}


void _runLight(void* params){
	// In future we could use this for some INIT values
	
	while (1) {
		lightTask_run();
	}
}