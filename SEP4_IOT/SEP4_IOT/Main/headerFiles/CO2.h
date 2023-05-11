#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <task.h>
#include <semphr.h>
#include <stdbool.h>
#include <serial.h>
#include <mh_z19.h>


void co2Task_run();
void co2Task_create();
void _runCO2(void* params);