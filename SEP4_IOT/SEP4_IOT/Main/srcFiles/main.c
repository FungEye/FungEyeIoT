#include "../headerFiles/CO2.h"
#include "../headerFiles/HumidityTemperature.h"
#include "../headerFiles/Light.h"

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
float luxValue;

// Callback function for TSL2591 driver
	void tsl2591Callback(tsl2591_returnCode_t rc)
	{
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
				// Lux value available, use 'luxValue' variable
				printf("Lux: %5.4f\n", luxValue);

			}
			break;

			// Handle other return codes if needed
		}
	}

static void _initDrivers(void) {
	puts("Initializing drivers...");
	mh_z19_initialise(ser_USART3);
	hih8120_initialise();
	tsl2591_initialise(tsl2591Callback);
	
	lora_driver_initialise(ser_USART1, NULL); // Without down-link buffer
}


static void _createTasks()
{
	co2Task_create();
	humidityTemperatureTask_create();
	lightTask_create();
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



