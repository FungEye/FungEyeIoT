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
#include <queue.h>

#include "definitions.h"

// Parameters for OTAA join - You have got these in a mail from IHA
#define LORA_appEUI "F2DDE2E826DE9BA5"   /**< Application EUI for LoRaWAN OTAA join. */
#define LORA_appKEY "FA15F6404AD2D77F878514403C7422DD"   /**< Application key for LoRaWAN OTAA join. */


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
 * 
 * @param queue_Temp1 The queue handle for temperature values.
 * @param queue_Hum1 The queue handle for humidity values.
 * @param queueCo2 The queue handle for CO2 values.
 * @param queue_Light1 The queue handle for light intensity values.
 * @param _measuredEventGroup The event group handle for indicating measurement readiness.
 */
void lora_initializer(QueueHandle_t queue_Temp1, QueueHandle_t queue_Hum1, QueueHandle_t queueCo2, QueueHandle_t queue_Light1, EventGroupHandle_t _measuredEventGroup);

/**
 * @brief Receives data from the queues.
 * 
 * Receives data from the temperature, humidity, CO2, and light queues for further processing.
 */
void receive_from_queues();

/**
 * @brief Resets the queues.
 * 
 * Resets the temperature, humidity, CO2, and light queues.
 */
void reset_queues();

/**
 * @brief Sets the LoRaWAN payload.
 * 
 * Sets the LoRaWAN payload with the data to be sent.
 */
void setting_payload();

/**
 * @brief Gets the LoRaWAN downlink message.
 * 
 * Gets the LoRaWAN downlink message received from the network.
 */
void getting_downlink();

/**
 * @brief Sets up LoRaWAN uplink.
 * 
 * Sets up the LoRaWAN uplink for sending data.
 */
void lora_uplink_setup();

/**
 * @brief Sets up LoRaWAN downlink.
 * 
 * Sets up the LoRaWAN downlink for receiving messages.
 */
void lora_downlink_setup();