#include <gtest/gtest.h>
#include "../include/ToyRobot.h"

TEST(ToyRobotTest, ValidPlacement) 
{
	Robot robot;
	robot.initTableSize(5, 5);
	robot.place(0, 0, Dir::NORTH);
	EXPECT_EQ(robot.report(), "0, 0, NORTH");

	robot.place(3, 3, Dir::NORTH);
	EXPECT_EQ(robot.report(), "3, 3, NORTH");
}

TEST(ToyRobotTest, PlaceBeforeInitTable)
{
	Robot robot;
	try
	{
		robot.place(0, 0, Dir::NORTH);
		FAIL() << "Placing a robot before initialize table size should throw an error\n";
	}
	catch (const ToyRobotException& e)
	{
		EXPECT_STREQ("Must initialize table size before placing the robot", e.what());
	}
}

TEST(ToyRobotTest, ValidMovement)
{
	Robot robot;
	robot.initTableSize(5, 5);
	robot.place(0, 0, Dir::SOUTH);
	EXPECT_EQ(robot.report(), "0, 0, SOUTH");

	robot.move();
	EXPECT_EQ(robot.report(), "0, 1, SOUTH");
}

TEST(ToyRobotTest, InvalidMovement)
{
	Robot robot;
	robot.initTableSize(5, 5);
	robot.place(0, 0, Dir::NORTH);
	try
	{
		robot.move();
		FAIL() << "Moving the robot out of the table should throw an error\n";
	}
	catch (const ToyRobotException& e)
	{
		EXPECT_STREQ("Robot can not be moved out of the table", e.what());
	}
}

TEST(ToyRobotTest, RotationTest)
{
	Robot robot;
	robot.initTableSize(5, 5);
	robot.place(0, 0, Dir::NORTH);

	robot.rotateLeft();
	EXPECT_EQ(robot.report(), "0, 0, WEST");
	robot.rotateLeft();
	EXPECT_EQ(robot.report(), "0, 0, SOUTH");

	robot.rotateRight();
	EXPECT_EQ(robot.report(), "0, 0, WEST");
	robot.rotateRight();
	EXPECT_EQ(robot.report(), "0, 0, NORTH");
}

TEST(ToyRobotTest, MoveAndRotate)
{
	Robot robot;
	robot.initTableSize(5, 5);
	robot.place(0, 0, Dir::NORTH);

	robot.rotateRight();
	EXPECT_EQ(robot.report(), "0, 0, EAST");
	robot.move();
	EXPECT_EQ(robot.report(), "1, 0, EAST");

	robot.rotateRight();
	EXPECT_EQ(robot.report(), "1, 0, SOUTH");
	robot.move();
	EXPECT_EQ(robot.report(), "1, 1, SOUTH");
}