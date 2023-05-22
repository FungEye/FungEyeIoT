/**
 * @file CO2.c
 * @brief Source file for measuring CO2.
 */

// Most of the imports are done in the Header file.
#include "../headerFiles/CO2.h"

int16_t co2; // CO2 value
EventGroupHandle_t _measuredEventGroup;

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

    xEventGroupWaitBits(_measuredEventGroup,
                            BIT_TASK_CO2_EMPTY,
                            pdFALSE,
                            pdTRUE,
                            portMAX_DELAY);
    mh_z19_returnCode_t rc;

    rc = mh_z19_takeMeassuring();  // We try to make a measurement
    if (rc != MHZ19_OK)
    {
        puts("CO2 MEASURING FAILED");  // Something went wrong
    }

	mh_z19_getCo2Ppm;

	printf("CO2: %d \n", co2);

    xEventGroupSetBits(_measuredEventGroup, BIT_TASK_CO2_READY);
	checking_emergency_values();
    vTaskDelay(pdMS_TO_TICKS(60000));   // 6 seconds delay between measurements
}

void checking_emergency_values(){
    if (co2 > 1000)
	{
		servo_open();
		vTaskDelay(pdMS_TO_TICKS(2000));
		servo_close();
	}else
	{
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
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
