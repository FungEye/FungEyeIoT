// Most of the imports are done in Header file.
#include "../headerFiles/HumidityTemperature.h"

// Would be great idea to make it static.
int16_t temperature;
int16_t humidity;


void initialize_HumidityTemperature(){
	hih8120_initialise();
}
// Function responsible for measuring Humidity and Temperature.
void humidityTemperatureTask_run()
{
		if (hih8120_wakeup() == HIH8120_OK) {
			vTaskDelay(pdMS_TO_TICKS(100));
			
			if (hih8120_measure() == HIH8120_OK) {
				vTaskDelay(pdMS_TO_TICKS(50));
				humidity = hih8120_getHumidityPercent_x10();
				temperature = hih8120_getTemperature_x10();
				printf("TEMP: %d\n",temperature);
				printf("HUMID: %d\n",humidity);
				} else {
				printf("FAILED: to measure - Humidity-Temperature");
			}
			} else {
			printf("FAILED: to wakeup - Humidity-Temperature");
			}
			
	
		vTaskDelay(pdMS_TO_TICKS(6000));
}

// Creating task for Humidity and Temperature.
// Being called from main.c
void humidityTemperatureTask_create(){
	xTaskCreate(
	_run,				       // Name of method
	"HumidityTemperature",						   // A name just for humans
	configMINIMAL_STACK_SIZE,	   // This stack size can be checked & adjusted by reading the Stack Highwater
	NULL,					   	   // (void *pvParameters)
	1,							   //the priority of the task
	NULL							   //No TaskHandle created.
	);
}

// Main task for Temperature-Humidity
void _run(void* params) {
	// In future we could use this for some INIT values
	
	while (1) {
		humidityTemperatureTask_run();
	}
}







