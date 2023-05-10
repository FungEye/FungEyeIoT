#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <task.h>
#include <semphr.h>
#include <stdbool.h>
#include <serial.h>
#include <tsl2591.h>


void lightTask_run();
void lightTask_create();
void _runLight(void* params);
void tsl2591Callback(tsl2591_returnCode_t rc);