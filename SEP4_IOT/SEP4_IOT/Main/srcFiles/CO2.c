/**
 * @file CO2.c
 * @brief Source file for measuring CO2.
 */

// Most of the imports are done in the Header file.
#include "../headerFiles/CO2.h"

int16_t co2; // CO2 value
SemaphoreHandle_t semaphoreCO2; // Semaphore for CO2

void myCo2CallBack(uint16_t ppm)
{
    co2 = ppm;
}

void initialize_CO2()
{
    mh_z19_initialise(ser_USART3);
    mh_z19_injectCallBack(myCo2CallBack);
}

void co2Task_run()
{
    vTaskDelay(pdMS_TO_TICKS(6000));   // 6 seconds delay between measurements

    xSemaphoreTake(semaphoreCO2, portMAX_DELAY);

    mh_z19_returnCode_t rc;

    rc = mh_z19_takeMeassuring();  // We try to make a measurement
    if (rc != MHZ19_OK)
    {
        puts("CO2 MEASURING FAILED");  // Something went wrong
    }
    co2 = mh_z19_getCo2Ppm;
	printf("CO2: %d \n", co2);
	if (co2 > 1000)
	{
		servo_open();
		vTaskDelay(pdMS_TO_TICKS(2000));
		servo_close();
	}else
	{
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
    
    xSemaphoreGive(semaphoreCO2); // Give the measured value to the semaphore to access later in LoRaWAN
}

void co2Task_create()
{
    xTaskCreate(
        _runCO2,                     // Name of the method
        "CO2",                       // A name just for humans
        configMINIMAL_STACK_SIZE,    // This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,                        // (void *pvParameters)
        1,                           // The priority of the task
        NULL                         // No TaskHandle created.
    );
}

void _runCO2(void* params)
{
    while (1)
    {
        co2Task_run();
    }
}
