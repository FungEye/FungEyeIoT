/**
 * @file Servo.c
 * @brief Source file for servo related operations
 */

#include "../headerFiles/Servo.h"

void initialize_Servo(){
    rc_servo_initialise();
	rc_servo_setPosition (0, 0);
}

void servo_open() {
    rc_servo_setPosition (0, 100);
}

void servo_close() {
    rc_servo_setPosition (0, -100);
}