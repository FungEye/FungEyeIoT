/**
 * @file CO2.h
 * @brief Header file for CO2-related functions and tasks.
 */

#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <task.h>
#include <semphr.h>
#include <stdbool.h>
#include <serial.h>
#include <mh_z19.h>
#include "Servo.h"

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
void initialize_CO2();
