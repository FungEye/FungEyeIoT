/**
 * @file HumidityTemperature.c
 * @brief Source file for measuring humidity and temperature.
 */

// Most of the imports are done in the Header file.
#include "../headerFiles/HumidityTemperature.h"

int16_t temperature; // Temperature value
int16_t humidity; // Humidity value
EventGroupHandle_t _measuredEventGroup;
QueueHandle_t my_queue_temp;
QueueHandle_t my_queue_hum;

void initialize_HumidityTemperature(QueueHandle_t queue_Temp, QueueHandle_t queue_Hum) {
    my_queue_temp = queue_Temp;
    my_queue_hum = queue_Hum;
    hih8120_initialise();
}


void humidityTemperatureTask_run() {
    vTaskDelay(pdMS_TO_TICKS(6000));   // 6 seconds delay between measurements
    
    if (hih8120_wakeup() == HIH8120_OK) {
    vTaskDelay(pdMS_TO_TICKS(100));

    xEventGroupWaitBits(_measuredEventGroup,
                            BIT_TASK_TEMP_EMPTY | BIT_TASK_HUM_EMPTY,
                            pdFALSE,
                            pdTRUE,
                            portMAX_DELAY);

            if (hih8120_measure() == HIH8120_OK) {
                vTaskDelay(pdMS_TO_TICKS(1000));
                humidity = hih8120_getHumidityPercent_x10(); // Using the 10x form to make sure there is not any weird meassurement converrtions
				
				vTaskDelay(pdMS_TO_TICKS(1000));
                temperature = hih8120_getTemperature_x10();
			    printf("TEMP: %d \n", temperature);
			    printf("HUM: %d \n", humidity);

                enqueue_Temp();
                enqueue_Hum();

                xEventGroupSetBits(_measuredEventGroup, BIT_TASK_TEMP_READY);
				xEventGroupSetBits(_measuredEventGroup, BIT_TASK_HUM_READY);

				vTaskDelay(pdMS_TO_TICKS(60000));   // 6 seconds delay between measurements
            } else {
            // printf("FAILED to measure humidity and temperature");
            }
    } else {
        // printf("FAILED to wake up humidity and temperature sensor");
    }
}

void humidityTemperatureTask_create() {
    xTaskCreate(
        _run,                       // Name of method
        "HumidityTemperature",      // A name just for humans
        configMINIMAL_STACK_SIZE,   // This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,                       // (void *pvParameters)
        1,                          // The priority of the task
        NULL                        // No TaskHandle created.
    );
}

void _run(void* params) {
    while (1) {
        humidityTemperatureTask_run();
    }
}

void enqueue_Temp(){
		long ok = xQueueSend(my_queue_temp, (void*) &temperature, 0 );
		puts(ok ? "Temperature enqued: OK" : "Temperature enqued: FAILED");
}

void enqueue_Hum(){
		long ok = xQueueSend(my_queue_hum, (void*) &humidity, 0 );
		puts(ok ? "Humidity enqued: OK" : "Humidity enqued: FAILED");
}