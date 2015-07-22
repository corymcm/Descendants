#include "stdafx.h"
#include "gtest/gtest.h"
#include "main.h"

TEST(Test, GTest)
{
	EXPECT_EQ(0, 0);
}

int main(int argc, char **argv)
{
	int ret = 0;
	::testing::InitGoogleTest(&argc, argv);
	ret = RUN_ALL_TESTS();
	return ret;
}
