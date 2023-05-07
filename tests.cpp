#include "gtest/gtest.h"

// Include interfaces and define global variables
// defined by the production code
extern "C"
{
}

// Create Fake Driver functions


// Create Test fixture and Reset all Mocks before each test
class Test_production : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	void TearDown() override
	{}
};


TEST_F(Test_production, Test1) {
	ASSERT_EQ(1, 1);
}

