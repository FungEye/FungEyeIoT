#include "gtest/gtest.h"
#include "fff.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
#include "servo_defs.h"
// Include interfaces and define global variables
// defined by the production code
extern "C"
{
	#include "Servo.h"
	#include "rc_servo.h"
}

// Create Test fixture and Reset all Mocks before each test
class Test_production : public ::testing::Test
{
protected:
	void SetUp() override
	{
		// //servo
		RESET_FAKE(rc_servo_initialise);
		RESET_FAKE(rc_servo_setPosition);

		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

TEST_F(Test_production, servo_initialization) {
    //clearing call count
    rc_servo_initialise_fake.call_count = 0;
    rc_servo_setPosition_fake.call_count = 0;

	initialize_Servo();
    
	ASSERT_EQ(rc_servo_initialise_fake.call_count, 1);
    ASSERT_EQ(rc_servo_setPosition_fake.call_count, 1);
    ASSERT_EQ(rc_servo_setPosition_fake.arg0_val, 0);
    ASSERT_EQ(rc_servo_setPosition_fake.arg1_val, 0);
}


TEST_F(Test_production, servo_opening) {
    //clearing call count
    rc_servo_setPosition_fake.call_count = 0;

	servo_open();
    
    ASSERT_EQ(rc_servo_setPosition_fake.call_count, 1);
    ASSERT_EQ(rc_servo_setPosition_fake.arg0_val, 0);
    ASSERT_EQ(rc_servo_setPosition_fake.arg1_val, 100);
}



TEST_F(Test_production, servo_closing) {
    //clearing call count
    rc_servo_setPosition_fake.call_count = 0;

	servo_close();
    
    ASSERT_EQ(rc_servo_setPosition_fake.call_count, 1);
    ASSERT_EQ(rc_servo_setPosition_fake.arg0_val, 0);
    ASSERT_EQ(rc_servo_setPosition_fake.arg1_val, -100);
}


