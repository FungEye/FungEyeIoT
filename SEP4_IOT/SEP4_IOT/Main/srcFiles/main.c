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

#include "semphr.h"

// Semaphores
SemaphoreHandle_t semaphoreTempHum; // Semaphore for Temperature and Humidity
SemaphoreHandle_t semaphoreCO2; // Semaphore for CO2
SemaphoreHandle_t semaphoreLight; // Semaphore for Light

// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);

/**
 * @brief Initializes the drivers.
 * 
 * This function initializes the CO2, HumidityTemperature, Light, and LoRaWAN drivers.
 */
static void _initDrivers(void) {
    puts("Initializing drivers...");
    initialize_CO2(); // Initializing CO2 driver
    initialize_HumidityTemperature(); // Initializing HumidityTemperature driver
    initialize_Light(); // Initializing Light driver
    lora_initializer(); // Initializing LoRaWAN driver
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

/**
 * @brief Main function.
 * 
 * This is the entry point of the program.
 * It initializes drivers, creates tasks, and starts the FreeRTOS scheduler.
 * 
 * @return Returns 0 on successful execution.
 */
int main(void) {
    stdio_initialise(ser_USART0); // Initializing stdio driver
    lora_handler_initialise(3); // Initializing LoRaWAN handler with priority 3

    semaphoreTempHum = xSemaphoreCreateBinary(); // Creating binary semaphore for Temperature and Humidity
    semaphoreCO2 = xSemaphoreCreateBinary(); // Creating binary semaphore for CO2
    semaphoreLight = xSemaphoreCreateBinary(); // Creating binary semaphore for Light
    xSemaphoreGive(semaphoreTempHum); // Giving initial value to semaphore
    xSemaphoreGive(semaphoreCO2); // Giving initial value to semaphore
    xSemaphoreGive(semaphoreLight); // Giving initial value to semaphore

    _initDrivers(); // Initializing drivers
    _createTasks(); // Creating tasks

    status_leds_initialise(5); // Initializing status LED driver with priority 5 (LoRaWAN)

    printf("Starting...\n");
    vTaskStartScheduler(); // Starting the FreeRTOS scheduler

    return 0;
}
