/**
 * @file Servo.h
 * @brief Header file for servo-related functions.
 */

#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <task.h>
#include <stdbool.h>
#include <serial.h>
#include <rc_servo.h>
#include <event_groups.h>


/**
 * @brief Initializes the servo.
 * 
 * Initializes the servo by setting up necessary configurations.
 */
void initialize_Servo();

/**
 * @brief Opens the servo.
 * 
 * Opens the servo
 */
void servo_open();

/**
 * @brief Closes the servo.
 * 
 * Closes the servo
 */
void servo_close();
