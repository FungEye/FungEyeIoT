/*
 * Light.c
 *
 * Created: 10/05/2023 10:43:00
 *  Author: ninaw
 */ 

#include "../headerFiles/Light.h"

float luxValue;
uint16_t luxInInt;

//Event group
EventGroupHandle_t _measuredEventGroupLight;

//Queue
QueueHandle_t my_queue;

// Callback function for TSL2591 driver
void tsl2591Callback(tsl2591_returnCode_t rc)
{
    switch (rc)
    {
        case TSL2591_DATA_READY:

        xEventGroupWaitBits(_measuredEventGroupLight,
                            BIT_TASK_LIGHT_EMPTY,
                            pdFALSE,
                            pdTRUE,
                            portMAX_DELAY);

            if (TSL2591_OK == tsl2591_getLux(&luxValue))
            {
                luxInInt = (uint16_t)luxValue;
            }

            enqueue_Light();

            xEventGroupSetBits(_measuredEventGroupLight, BIT_TASK_LIGHT_READY);
            vTaskDelay(pdMS_TO_TICKS(60000));   // 6 seconds delay between measurements
            break;

        case TSL2591_OK:
            // Last command performed successfully
            break;

        case TSL2591_DEV_ID_READY:
            // Dev ID now fetched
            break;

        default:
            break;
    }
}

void initialize_Light(QueueHandle_t queue_Light, EventGroupHandle_t _measuredEventGroup)
{
	_measuredEventGroupLight = _measuredEventGroup;
    my_queue = queue_Light;
    if (TSL2591_OK == tsl2591_initialise(tsl2591Callback))
    {
        // Driver initialized successfully
    }
}

void lightTask_run()
{
    if (TSL2591_OK == tsl2591_enable())
    {
        // The power-up command is now sent to the sensor
        // It can be powered down with a call to tsl2591_disable()
    }
    vTaskDelay(pdMS_TO_TICKS(6000));

    tsl2591_returnCode_t fetchDataStatus = tsl2591_fetchData();

    if (fetchDataStatus == TSL2591_OK)
    {
        printf("Light data fetched!\n");
         //Callback
    }
    else if (fetchDataStatus == TSL2591_BUSY)
    {
        printf("Light sensor busy\n");
    }
    else if (fetchDataStatus == TSL2591_DRIVER_NOT_INITIALISED)
    {
        printf("Light driver not initialized\n");
    }

}

void lightTask_create()
{
    xTaskCreate(
        _runLight,                  // Name of method
        "Light",                    // A name just for humans
        configMINIMAL_STACK_SIZE,   // This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,                       // (void *pvParameters)
        1,                          // the priority of the task
        NULL
    );
}

void _runLight(void* params)
{
    // In the future, we could use this for some INIT values
    while (1)
    {
        lightTask_run();
    }
}

void enqueue_Light(){
		long ok = xQueueSend(my_queue, (void*) &luxInInt, 0 );
		puts(ok ? "Light enqued: OK" : "Light enqued: FAILED");
}