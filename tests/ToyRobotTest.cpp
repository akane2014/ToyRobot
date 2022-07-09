#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/ToyRobot.h"

using ::testing::AtLeast;

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

TEST(ToyRobotTest, InvalidPlacement)
{
	Robot robot;
	robot.initTableSize(5, 5);
	try
	{
		robot.place(6, 6, Dir::NORTH);
		FAIL() << "Placing a robot outside of the table should throw an error\n";
	}
	catch (const ToyRobotException& e)
	{
		EXPECT_STREQ("The robot must be placed inside the table", e.what());
	}
}

TEST(ToyRobotTest, ValidMovement)
{
	Robot robot;
	robot.initTableSize(5, 5);
	robot.place(0, 0, Dir::SOUTH);
	EXPECT_EQ(robot.report(), "0, 0, SOUTH");

	EXPECT_TRUE(robot.move());
	EXPECT_EQ(robot.report(), "0, 1, SOUTH");
}

TEST(ToyRobotTest, InvalidMovement)
{
	Robot robot;
	robot.initTableSize(5, 5);
	robot.place(0, 0, Dir::NORTH);
	EXPECT_FALSE(robot.move());
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

TEST(ToyRobotTest, CombinationWithInvalidMove)
{
	Robot robot;
	robot.initTableSize(5, 5);
	robot.place(4, 4, Dir::NORTH);

	robot.rotateLeft();
	robot.move();
	robot.rotateLeft();
	robot.move();
	robot.rotateRight();
	robot.move();
	EXPECT_EQ(robot.report(), "2, 4, WEST");
}

//Controller

class MockRobot : public IRobot {
public:
	MOCK_METHOD2(initTableSize, void(int _w, int _h));
	MOCK_METHOD3(place, void(int _x, int _y, Dir _dir));
	MOCK_METHOD0(move, bool());
	MOCK_METHOD0(rotateLeft, void());
	MOCK_METHOD0(rotateRight, void());
	MOCK_CONST_METHOD0(report, std::string());
};

class RobotControllerTest : public ::testing::Test {
protected:
	RobotControllerTest() : robot(), controller(robot)
	{
		robot.initTableSize(5, 5);
	}

	MockRobot robot;
	RobotController controller;
};

TEST_F(RobotControllerTest, BasicControlTest)
{
	EXPECT_CALL(robot, place(0, 0, Dir::NORTH)).Times(1);
	controller.processCommand("PLACE 0,0,NORTH");

	EXPECT_CALL(robot, place(1, 3, Dir::SOUTH)).Times(1);
	controller.processCommand("PLACE 1,3,SOUTH");

	EXPECT_CALL(robot, move()).Times(1);
	controller.processCommand("MOVE");

	EXPECT_CALL(robot, rotateLeft()).Times(1);
	controller.processCommand("LEFT");

	EXPECT_CALL(robot, rotateRight()).Times(1);
	controller.processCommand("RIGHT");

	EXPECT_CALL(robot, report()).Times(1);
	controller.processCommand("REPORT");
}

TEST_F(RobotControllerTest, InvalidControlCommand)
{
	try
	{
		controller.processCommand("STOP");
		FAIL() << "Invalid STOP command should throw an error\n";
	}
	catch (const ToyRobotException& e)
	{
		EXPECT_STREQ("Unexpected command:STOP", e.what());
	}

	try
	{
		controller.processCommand("PLACE one,0,NORTH");
		FAIL() << "Invalid parameters for PLACE command should throw an error\n";
	}
	catch (const ToyRobotException& e)
	{
		EXPECT_STREQ("Invalid input for PLACE command", e.what());
	}

	try
	{
		controller.processCommand("PLACE 4,4,SOUTHWEST");
		FAIL() << "Invalid parameters for PLACE command should throw an error\n";
	}
	catch (const ToyRobotException& e)
	{
		EXPECT_STREQ("Invalid input for PLACE command", e.what());
	}
}