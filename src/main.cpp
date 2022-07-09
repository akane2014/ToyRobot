#include <iostream>
#include <string>
#include <fstream>

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

	std::string line;
	std::ifstream myfile(argv[1]);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			controller.processCommand(line);
		}
		myfile.close();
	}
	else
	{
		std::cout << "Can not open commands file" << std::endl;
	}

	return 0;
}