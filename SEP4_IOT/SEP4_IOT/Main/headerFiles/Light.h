/**
 * @file Light.h
 * @brief Header file for light-related functions and tasks.
 */

#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <task.h>
#include <stdbool.h>
#include <serial.h>
#include <tsl2591.h>
#include <event_groups.h>
#include <queue.h>

#include "definitions.h"


/**
 * @brief Runs the light task.
 * 
 * Responsible for running the light task, which reads light intensity values from the sensor and performs necessary actions.
 */
void lightTask_run();

/**
 * @brief Creates the light task.
 * 
 * Creates and initializes the light task responsible for reading light intensity values from the sensor and processing them.
 */
void lightTask_create();

/**
 * @brief Internal function to run the light task.
 * 
 * An internal helper function used by the light task to perform the main operations.
 * 
 * @param params Task parameters (not used).
 */
void _runLight(void* params);

/**
 * @brief Initializes the light sensor.
 * 
 * Initializes the light sensor by setting up necessary configurations.
 * 
 * @param queue_Light The queue handle for light intensity values.
 * @param _measuredEventGroup The event group handle for indicating measurement readiness.
 */
void initialize_Light(QueueHandle_t queue_Light, EventGroupHandle_t _measuredEventGroup);

/**
 * @brief Callback function for the light sensor.
 * 
 * Called when a new light intensity value is received from the sensor.
 * 
 * @param rc The return code from the light sensor.
 */
void tsl2591Callback(tsl2591_returnCode_t rc);

/**
 * @brief Enqueues light intensity values.
 * 
 * Enqueues light intensity values for further processing.
 */
void enqueue_Light();
