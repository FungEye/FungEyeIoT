/**
 * @file HumidityTemperature.h
 * @brief Header file for humidity and temperature-related functions and tasks.
 */

#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <task.h>
#include <stdbool.h>
#include <serial.h>
#include <hih8120.h>
#include <event_groups.h>
#include <queue.h>

#include "definitions.h"

/**
 * @brief Runs the humidity and temperature task.
 * 
 * Responsible for running the humidity and temperature task, which reads humidity and temperature values from the sensor and performs necessary actions.
 */
void humidityTemperatureTask_run();

/**
 * @brief Creates the humidity and temperature task.
 * 
 * Creates and initializes the humidity and temperature task responsible for reading humidity and temperature values from the sensor and processing them.
 */
void humidityTemperatureTask_create();

/**
 * @brief Internal function to run the humidity and temperature task.
 * 
 * An internal helper function used by the humidity and temperature task to perform the main operations.
 * 
 * @param params Task parameters (not used).
 */
void _run(void* params);

/**
 * @brief Initializes the humidity and temperature sensor.
 * 
 * Initializes the humidity and temperature sensor by setting up necessary configurations.
 * 
 * @param queue_Temp The queue handle for temperature values.
 * @param queue_Hum The queue handle for humidity values.
 * @param _measuredEventGroup The event group handle for indicating measurement readiness.
 */
void initialize_HumidityTemperature(QueueHandle_t queue_Temp, QueueHandle_t queue_Hum, EventGroupHandle_t _measuredEventGroup);

/**
 * @brief Enqueues temperature values.
 * 
 * Enqueues temperature values for further processing.
 */
void enqueue_Temp();

/**
 * @brief Enqueues humidity values.
 * 
 * Enqueues humidity values for further processing.
 */
void enqueue_Hum();
