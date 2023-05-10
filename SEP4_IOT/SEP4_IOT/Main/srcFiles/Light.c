/*
 * Light.c
 *
 * Created: 10/05/2023 10:43:00
 *  Author: ninaw
 */ 

#include "../headerFiles/Light.h"

// Define variables to store light data
extern float luxValue;


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
			printf("Lux: %f", luxValue);
			//puts("Lux: %d", luxValue);
		}
	
	tsl2591_disable();

	
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