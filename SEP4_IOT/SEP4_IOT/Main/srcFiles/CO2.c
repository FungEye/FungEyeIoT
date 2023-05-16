// Most of the imports are done in the Header file.
#include "../headerFiles/CO2.h"

// Would be a great idea to make it static.
int16_t co2;
SemaphoreHandle_t semaphoreCO2;

void myCo2CallBack(uint16_t ppm)
{
	co2 = ppm;
}

void initialize_CO2() {
	mh_z19_initialise(ser_USART3);
	mh_z19_injectCallBack(myCo2CallBack);
}



// Function responsible for measuring CO2
void co2Task_run() {
  vTaskDelay(pdMS_TO_TICKS(6000));

	xSemaphoreTake(semaphoreCO2, portMAX_DELAY);

	mh_z19_returnCode_t rc;
	
	rc = mh_z19_takeMeassuring();
	if (rc != MHZ19_OK)
	{
		puts("CO2 MEASURING FAILED");
	}
	//co2 = mh_z19_getCo2Ppm;
	mh_z19_getCo2Ppm;
	printf("CO2: %d\n",co2);
	vTaskDelay(pdMS_TO_TICKS(2000)); // TO CHANGE TO 6000
	
	xSemaphoreGive(semaphoreCO2);
	
}

// Creating task for CO2, called from main.c
void co2Task_create() {
	xTaskCreate(
	_runCO2,                     // Name of the method
	"CO2",                       // A name just for humans
	configMINIMAL_STACK_SIZE,    // This stack size can be checked & adjusted by reading the Stack Highwater
	NULL,                        // (void *pvParameters)
	1,                           // The priority of the task
	NULL                         // No TaskHandle created.
	);
}

// Main task for CO2
void _runCO2(void* params) {
	// In the future, we could use this for some INIT values
	while (1) {
		co2Task_run();
	}
}