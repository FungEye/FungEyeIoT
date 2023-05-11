/*
* loraWANHandler.h
*
* Created: 11/05/2023 15:16:00
*  Author: Group 2x
*/

#pragma once

#include <stddef.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <lora_driver.h>
#include <status_leds.h>

// Parameters for OTAA join - You have got these in a mail from IHA
#define LORA_appEUI "F2DDE2E826DE9BA5"
#define LORA_appKEY "FA15F6404AD2D77F878514403C7422DD"

void lora_handler_task( void *pvParameters );
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);
static void _lora_setup(void);
void lora_handler_task( void *pvParameters );