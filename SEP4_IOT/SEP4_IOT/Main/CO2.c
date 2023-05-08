// Most of the imports are done in Header file.
#include "CO2.h"

// Would be great idea to make it static.
int16_t co2;


// Function responsible for measuring CO2
void co2Task_run()	
{
	mh_z19_returnCode_t rc;
	
		rc = mh_z19_takeMeassuring();
		if (rc != MHZ19_OK)
		{
			puts("CO2 MEASURING FAILED");
		}
		co2 = mh_z19_getCo2Ppm;
		printf("CO2: %d\n",co2);
		vTaskDelay(pdMS_TO_TICKS(6000));
	
}

// Creating task for CO2
// Being called from main.c
void co2Task_create(){
	xTaskCreate(
	_runCO2,				       // Name of method
	"CO2",						   // A name just for humans
	configMINIMAL_STACK_SIZE,	   // This stack size can be checked & adjusted by reading the Stack Highwater
	NULL,					   	   // (void *pvParameters)
	1,							   //the priority of the task
	NULL							   //No TaskHandle created.
	);
}

// Main task for CO2. 
void _runCO2(void* params) {
	// In future we could use this for some INIT values
	
	while (1) {
		co2Task_run();
	}
}







