/**
 * @file loraWANHandler.h
 * @brief Header file for LoRaWAN handler functions and tasks.
 *
 * Created: 11/05/2023 15:16:00
 * Author: Group 2x
 */

#pragma once

#include <stddef.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <lora_driver.h>
#include <status_leds.h>
#include "Servo.h"

#include <event_groups.h>

#include "definitions.h"

// Parameters for OTAA join - You have got these in a mail from IHA
#define LORA_appEUI "F2DDE2E826DE9BA5"
#define LORA_appKEY "FA15F6404AD2D77F878514403C7422DD"


/**
 * @brief LoRaWAN handler task.
 * 
 * This task handles LoRaWAN communication and related tasks.
 * 
 * @param pvParameters Task parameters (not used).
 */
void lora_handler_task(void *pvParameters);

/**
 * @brief Initializes the LoRaWAN handler.
 * 
 * Initializes the LoRaWAN handler by setting up necessary configurations.
 * 
 * @param lora_handler_task_priority The priority of the LoRaWAN handler task.
 */
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);

/**
 * @brief Sets up LoRaWAN configurations.
 * 
 * Performs the setup of LoRaWAN configurations for OTAA join.
 * It includes setting the application EUI and application key.
 */
static void _lora_setup(void);

/**
 * @brief LoRaWAN downlink task.
 * 
 * This task handles downlink messages received from the LoRaWAN network.
 * 
 * @param pvParameters Task parameters (not used).
 */
void lora_downlink_task(void *pvParameters);

/**
 * @brief Initializes the LoRaWAN driver.
 * 
 * Initializes the LoRaWAN driver by setting up necessary configurations.
 */
void lora_initializer();
