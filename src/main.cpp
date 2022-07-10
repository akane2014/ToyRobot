#include <iostream>

#include "ToyRobot.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " commandsFile" << std::endl;
		return -1;
	}

	Robot robot;
	robot.initTableSize(5, 5);

	RobotController controller(robot);
	controller.executeFile(argv[1], std::cout);

	return 0;
}