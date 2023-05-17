/**
 * @file CO2.c
 * @brief Source file for CO2-related functions and tasks.
 */

// Most of the imports are done in the Header file.
#include "../headerFiles/CO2.h"

int16_t co2; // CO2 value
SemaphoreHandle_t semaphoreCO2; // Semaphore for CO2

void myCo2CallBack(uint16_t ppm)
{
    co2 = ppm;
}

void initialize_CO2() {
    mh_z19_initialise(ser_USART3);
    mh_z19_injectCallBack(myCo2CallBack);
}

void co2Task_run() {
    vTaskDelay(pdMS_TO_TICKS(6000));

    xSemaphoreTake(semaphoreCO2, portMAX_DELAY);

    mh_z19_returnCode_t rc;

    rc = mh_z19_takeMeassuring();
    if (rc != MHZ19_OK)
    {
        puts("CO2 MEASURING FAILED");
    }
    co2 = mh_z19_getCo2Ppm;
    vTaskDelay(pdMS_TO_TICKS(2000));

    xSemaphoreGive(semaphoreCO2);
}

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

void _runCO2(void* params) {
    while (1) {
        co2Task_run();
    }
}
