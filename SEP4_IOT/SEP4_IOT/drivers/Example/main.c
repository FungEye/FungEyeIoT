/*
* main.c
* Author : IHA
*
* Example main file including LoRaWAN setup
* Just for inspiration :)
*/

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio_driver.h>
#include <serial.h>

 // Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>

//SENSEROS
//Humidity & Temperature
#include <hih8120.h>

// define semaphore handle
SemaphoreHandle_t xTestSemaphore;

// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);

/*-----------------------------------------------------------*/
void initialiseSystem()
{
	// Set output ports for leds used in the example
	DDRA |= _BV(DDA4) | _BV(DDA5);

	// Make it possible to use stdio on COM port 0 (USB)
	// on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);
	
	// vvvvvvvvvvvvvvvvv BELOW IS LoRaWAN initialisation vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Status Leds driver
	status_leds_initialise(5); // Priority 5 for internal task
	// Initialise the LoRaWAN driver without down-link buffer
	lora_driver_initialise(1, NULL);
	// Create LoRaWAN task and start it up with priority 3
	lora_handler_initialise(3);
}

void readTempHum()
{
	printf("----Start----");
	if ( HIH8120_OK == hih8120_initialise())
	{
		float humidity = 0.0;
		float temp = 0.0;
		
		if (HIH8120_OK != hih8120_wakeup())
		{
			puts("shits fucked 1");
		}
		if (HIH8120_OK != hih8120_measure())
		{
			puts("shits fucked 2");
		}
		humidity = hih8120_getHumidity();
		temp = hih8120_getTemperature();
		printf("----Start----");
		printf("----END----");
	}
}

/*-----------------------------------------------------------*/
int main(void)
{
	//ASK HOW THIS WORKS
	initialiseSystem(); // Must be done as the very first thing!!
	printf("Program Started!!\n");
	readTempHum();
	vTaskStartScheduler(); // Initialise and run the freeRTOS scheduler. Execution should never return from here.
}

