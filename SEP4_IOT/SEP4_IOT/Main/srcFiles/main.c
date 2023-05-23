/**
 * @file main.c
 * @brief Main file for the project.
 */

#include "../headerFiles/CO2.h" // Including CO2 header file
#include "../headerFiles/HumidityTemperature.h" // Including HumidityTemperature header file
#include "../headerFiles/Light.h" // Including Light header file
#include "../headerFiles/LoRaWANHandler.h" // Including LoRaWANHandler header file

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>

#include <stdio_driver.h>
#include <serial.h>

#include <lora_driver.h> // Including LoRaWAN driver
#include <status_leds.h>

#include <event_groups.h>
#include "../headerFiles/definitions.h"
#include <queue.h>


//Event groups
EventGroupHandle_t _measuredEventGroup = NULL;

//Queues
QueueHandle_t queue_CO2 = NULL;
QueueHandle_t queue_Temp = NULL;
QueueHandle_t queue_Hum = NULL;
QueueHandle_t queue_Light = NULL;


// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);

/**
 * @brief Initializes the drivers.
 * 
 * This function initializes the CO2, HumidityTemperature, Light, and LoRaWAN drivers.
 */
static void _initDrivers(void) {
    puts("Initializing drivers...");
    initialize_CO2(queue_CO2, _measuredEventGroup); // Initializing CO2 driver
    initialize_HumidityTemperature(queue_Temp, queue_Hum, _measuredEventGroup); // Initializing HumidityTemperature driver
    initialize_Light(queue_Light, _measuredEventGroup); // Initializing Light driver
    lora_initializer(queue_Temp, queue_Hum, queue_CO2, queue_Light, _measuredEventGroup); // Initializing LoRaWAN driver
    initialize_Servo(); // Initializing Servo driver
}

/**
 * @brief Creates tasks.
 * 
 * This function creates tasks for CO2, Humidity and Temperature, and Light.
 */
static void _createTasks() {
    co2Task_create(); // Creating task for CO2
    humidityTemperatureTask_create(); // Creating task for Humidity and Temperature
    lightTask_create(); // Creating task for Light
}

static void createEventGroups(){
    _measuredEventGroup = xEventGroupCreate();
}

static void createQueues(){
    queue_CO2 = xQueueCreate(1, sizeof(int));
    queue_Temp = xQueueCreate(1, sizeof(int));
    queue_Hum = xQueueCreate(1, sizeof(int));
    queue_Light = xQueueCreate(1, sizeof(int));
}
/**
 * @brief Main function.
 * 
 * This is the entry point of the program.
 * It initializes drivers, creates tasks, and starts the FreeRTOS scheduler.
 * 
 * @return Returns 0 on successful execution.
 */
int main(void) {
	printf("starting!");
    stdio_initialise(ser_USART0); // Initializing stdio driver
    lora_handler_initialise(3); // Initializing LoRaWAN handler with priority 3

    createEventGroups();
    createQueues();

    _initDrivers(); // Initializing drivers
    _createTasks(); // Creating tasks

    status_leds_initialise(5); // Initializing status LED driver with priority 5 (LoRaWAN)

    printf("Starting...\n");
    vTaskStartScheduler(); // Starting the FreeRTOS scheduler

	while(1){
		
	}
    return 0;
}
