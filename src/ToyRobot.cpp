#include "../include/ToyRobot.h"

#include <sstream>

using namespace std;

//Utils

std::string dirToString(Dir dir)
{
	std::string result;
	switch (dir)
	{
	case Dir::NORTH:
		result = "NORTH";
		break;
	case Dir::EAST:
		result = "EAST";
		break;
	case Dir::SOUTH:
		result = "SOUTH";
		break;
	case Dir::WEST:
		result = "WEST";
		break;
	}
	return result;
}

Dir stringToDir(std::string s_dir)
{
	if (s_dir == "NORTH")
	{
		return Dir::NORTH;
	}
	else if (s_dir == "EAST")
	{
		return Dir::EAST;
	}
	else if (s_dir == "SOUTH")
	{
		return Dir::SOUTH;
	}
	else if (s_dir == "WEST")
	{
		return Dir::WEST;
	}
	else
	{
		throw std::exception("Invalid direction");
	}
}

void toDelta(Dir dir, int& delta_x, int& delta_y)
{
	switch (dir)
	{
	case Dir::NORTH:
		delta_x = 0;
		delta_y = -1;
		break;
	case Dir::EAST:
		delta_x = 1;
		delta_y = 0;
		break;
	case Dir::SOUTH:
		delta_x = 0;
		delta_y = 1;
		break;
	case Dir::WEST:
		delta_x = -1;
		delta_y = 0;
		break;
	}
}

Dir dirRotateLeft(Dir dir)
{
	int dir_index = (int)dir;
	dir_index--;
	if (dir_index < 0)
	{
		dir_index = DIR_NUM - 1;
	}
	return (Dir)dir_index;
}

Dir dirRotateRight(Dir dir)
{
	int dir_index = (int)dir;
	dir_index++;
	if (dir_index >= DIR_NUM)
	{
		dir_index = 0;
	}
	return (Dir)dir_index;
}

//Robot

void Robot::initTableSize(int _w, int _h)
{
	table_inited = true;
	table_w = _w;
	table_h = _h;
}

void Robot::place(int _x, int _y, Dir _dir)
{
	if (!table_inited)
	{
		throw ToyRobotException("Must initialize table size before placing the robot");
	}

	if (_x >= 0 && _x < table_w && _y >= 0 && _y < table_h)
	{
		x = _x;
		y = _y;
		dir = _dir;
		is_placed = true;
	}
	else
	{
		throw ToyRobotException("The robot must be placed inside the table");
	}
}

bool Robot::move()
{
	if (is_placed)
	{
		int delta_x = 0;
		int delta_y = 0;
		toDelta(dir, delta_x, delta_y);
		int new_x = x + delta_x;
		int new_y = y + delta_y;
		if (new_x >= table_w || new_x < 0 || new_y >= table_h || new_y < 0)
		{
			return false;
		}
		else
		{
			x = new_x;
			y = new_y;
			return true;
		}
	}
}

void Robot::rotateLeft()
{
	if (is_placed)
	{
		dir = dirRotateLeft(dir);
	}
}

void Robot::rotateRight()
{
	if (is_placed)
	{
		dir = dirRotateRight(dir);
	}
}

string Robot::report() const
{
	if (is_placed)
	{
		return std::to_string(x) + ", " + std::to_string(y) + ", " + dirToString(dir);
	}
	else
	{
		return "";
	}
}

bool Robot::isReady() const
{
	return is_placed;
}

//Controller
void RobotController::processCommand(std::string command)
{
	std::stringstream ss(command);

	std::string keyword;
	getline(ss, keyword, ' ');

	if (keyword == "PLACE")
	{
		std::string s_value;
		int x, y;
		Dir dir;
		try
		{
			getline(ss, s_value, ',');
			x = stoi(s_value);
			getline(ss, s_value, ',');
			y = stoi(s_value);
			getline(ss, s_value);
			dir = stringToDir(s_value);
		}
		catch (std::exception& e)
		{
			throw ToyRobotException("Invalid input for PLACE command");
		}
		robot.place(x, y, dir);
	}
	else if (keyword == "MOVE")
	{
		if(robot.isReady())
			robot.move();
	}
	else if (keyword == "LEFT")
	{
		if (robot.isReady())
			robot.rotateLeft();
	}
	else if (keyword == "RIGHT")
	{
		if (robot.isReady())
			robot.rotateRight();
	}
	else if (keyword == "REPORT")
	{
		if (robot.isReady())
			robot.report();
	}
	else
	{
		throw ToyRobotException("Unexpected command:" + keyword);
	}
}

