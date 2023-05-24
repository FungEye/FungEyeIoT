#pragma once
#include "fff.h"

extern "C" {
// The simulated header files belonging to the test project
#include "Servo.h" 
#include "rc_servo.h"
}

DECLARE_FAKE_VOID_FUNC(rc_servo_initialise);
DECLARE_FAKE_VOID_FUNC(rc_servo_setPosition, uint8_t, int8_t);