#include "CO2.h"
#include "HumidityTemperature.h"

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>

#include <stdio_driver.h>
#include <serial.h>

// Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>

// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);

static void _initDrivers(void) {
	puts("Initializing drivers...");
	mh_z19_initialise(ser_USART3);
	hih8120_initialise();
	lora_driver_initialise(ser_USART1, NULL); // Without down-link buffer
}


static void _createTasks()
{
	co2Task_create();
	humidityTemperatureTask_create();
}


int main(void)
{
	stdio_initialise(ser_USART0);
	lora_handler_initialise(3); // Lora task with priority 3
	
	_initDrivers();
	_createTasks();

	status_leds_initialise(5); // Status LED driver - Priority 5. (LoRaWAN)

	printf("Starting...\n");
	vTaskStartScheduler();
}


