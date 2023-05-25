#include "servo_defs.h"

DEFINE_FAKE_VOID_FUNC(rc_servo_initialise);
DEFINE_FAKE_VOID_FUNC(rc_servo_setPosition, uint8_t, int8_t);