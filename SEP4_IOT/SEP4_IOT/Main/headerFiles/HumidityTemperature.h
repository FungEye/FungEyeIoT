#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <task.h>
#include <semphr.h>
#include <stdbool.h>
#include <serial.h>
#include <hih8120.h>
#include <display_7seg.h>

void humidityTemperatureTask_run();
void humidityTemperatureTask_create();
void _run(void* params);
void initialize_HumidityTemperature();