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
//CO2
#include <mh_z19.h>

// define two Tasks
void task1( void *pvParameters );
void task2( void *pvParameters );

// define semaphore handle
SemaphoreHandle_t xTestSemaphore;
int16_t humidity;
int16_t temperature;
int16_t co2;

// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);

/*-----------------------------------------------------------*/
void create_tasks_and_semaphores(void)
{
	// Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
	// because it is sharing a resource, such as the Serial port.
	// Semaphores should only be used whilst the scheduler is running, but we can set it up here.
	if ( xTestSemaphore == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		xTestSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		if ( ( xTestSemaphore ) != NULL )
		{
			xSemaphoreGive( ( xTestSemaphore ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}

	xTaskCreate(
	task1
	,  "HumidityTemperature"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );

	xTaskCreate(
	task2
	,  "CO2"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

/*-----------------------------------------------------------*/
void task1( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 500/portTICK_PERIOD_MS; // 500 ms

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		printf("----Temp & Humidity START----");
		humidity = 0.0;
		temperature = 0.0;
		
		puts("Tying to wake up");
		if (HIH8120_OK != hih8120_wakeup())
		{
			puts("WAKEUP FAILED");
		}else
		{
			puts("AWAKE");
		}
		vTaskDelay(pdMS_TO_TICKS(100));
		
		puts("Measuring");
		if (HIH8120_OK != hih8120_measure())
		{
			puts("MESURING FAILED");
		}else
		{
			puts("MESURING SUCCESSFUL");
		}
		humidity = hih8120_getHumidityPercent_x10();
		temperature = hih8120_getTemperature_x10();
		printf("TEMP: %d\n",temperature);
		printf("HUMID: %d\n",humidity);
		printf("----Temp & Humidity END----");
		vTaskDelay(pdMS_TO_TICKS(60000));
	}
}

/*-----------------------------------------------------------*/
void task2( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 1000/portTICK_PERIOD_MS; // 1000 ms

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	mh_z19_returnCode_t rc;

	for(;;)
	{
		printf("----CO2 START----");
		rc = mh_z19_takeMeassuring();
		if (rc != MHZ19_OK)
		{
			puts("CO2 MEASURING FAILED");
		}
		
		co2 = mh_z19_getCo2Ppm;
		printf("CO2: %d\n",co2);
		printf("----CO2 END----");
		vTaskDelay(pdMS_TO_TICKS(6000));
	}
}

/*-----------------------------------------------------------*/
void initialiseSystem()
{
	// Set output ports for leds used in the example
	DDRA |= _BV(DDA0) | _BV(DDA7);

	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);
	// Let's create some tasks
	create_tasks_and_semaphores();

	// vvvvvvvvvvvvvvvvv BELOW IS LoRaWAN initialisation vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Status Leds driver
	status_leds_initialise(5); // Priority 5 for internal task
	// Initialise the LoRaWAN driver without down-link buffer
	lora_driver_initialise(1, NULL);
	// Create LoRaWAN task and start it up with priority 3
	lora_handler_initialise(3);
	if(HIH8120_OK == hih8120_initialise())
	{
		puts("hih8120 INITAILISED");
	}else
	{
		puts("hih8120 FAILED");
	}
	
	// The parameter is the USART port the MH-Z19 sensor is connected to - in this case USART3
	mh_z19_initialise(ser_USART3);
	puts("mh_z19 INITAILISED");

}

/*-----------------------------------------------------------*/
int main(void)
{
	initialiseSystem(); // Must be done as the very first thing!!
	printf("Program Started!!\n");
	vTaskStartScheduler(); // Initialise and run the freeRTOS scheduler. Execution should never return from here.

	/* Replace with your application code */
	while (1)
	{
	}
}