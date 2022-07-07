#include <gtest/gtest.h>
#include "../include/ToyRobot.h"

TEST(ToyRobotTest, ValidPlacement) {
	Robot robot;
	robot.init(0, 0, Dir::NORTH);
	EXPECT_EQ(robot.report(), "0, 0, NORTH");
}