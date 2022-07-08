#include "../include/ToyRobot.h"

using namespace std;

//Utils

std::string toString(Dir dir)
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

	x = _x;
	y = _y;
	dir = _dir;
}

void Robot::move()
{
	int delta_x = 0;
	int delta_y = 0;
	toDelta(dir, delta_x, delta_y);
	int new_x = x + delta_x;
	int new_y = y + delta_y;
	if (new_x >= table_w || new_x < 0 || new_y >= table_h || new_y < 0)
	{
		throw ToyRobotException("Robot can not be moved out of the table");
	}
	else
	{
		x = new_x;
		y = new_y;
	}
}

void Robot::rotateLeft()
{
	dir = dirRotateLeft(dir);
}

void Robot::rotateRight()
{
	dir = dirRotateRight(dir);
}

string Robot::report()
{
	return std::to_string(x) + ", " + std::to_string(y) + ", " + toString(dir);
}

