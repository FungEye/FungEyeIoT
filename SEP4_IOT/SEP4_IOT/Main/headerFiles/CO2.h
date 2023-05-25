/**
 * @file CO2.h
 * @brief Header file for CO2-related functions and tasks.
 */

#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <task.h>
#include <stdbool.h>
#include <serial.h>
#include <mh_z19.h>
#include "Servo.h"
#include <event_groups.h>
#include <queue.h>

#include "definitions.h"

/**
 * @brief Runs the CO2 task.
 * 
 * Responsible for running the CO2 task, which reads CO2 values from the sensor and performs necessary actions.
 */
void co2Task_run();

/**
 * @brief Callback function for CO2 values.
 * 
 * Called when a new CO2 value is received from the sensor.
 * 
 * @param ppm The CO2 value in parts per million (ppm).
 */
void myCo2CallBack(uint16_t ppm);

/**
 * @brief Creates the CO2 task.
 * 
 * Creates and initializes the CO2 task responsible for reading CO2 values from the sensor and processing them.
 */
void co2Task_create();

/**
 * @brief Internal function to run the CO2 task.
 * 
 * An internal helper function used by the CO2 task to perform the main operations.
 * 
 * @param params Task parameters (not used).
 */
void _runCO2(void* params);

/**
 * @brief Initializes the CO2 sensor.
 * 
 * Initializes the CO2 sensor by setting up necessary configurations and registering the CO2 callback function.
 */
void initialize_CO2(QueueHandle_t queue_CO2, EventGroupHandle_t _measuredEventGroup);

/**
 * @brief Checks for emergency values related to CO2.
 * 
 * Checks the CO2 values for emergency levels (above 500000 ppm) and opens the servo if necessary.
 */
void checking_emergency_values();

/**
 * @brief Enqueues CO2 values.
 * 
 * Enqueues CO2 values for further processing.
 */
void enqueue_CO2();
