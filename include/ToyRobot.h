#pragma once

#include <string>

//Utils

class ToyRobotException : public std::runtime_error
{
public:
	ToyRobotException(const std::string& msg) : std::runtime_error{ msg } {}
};

enum class Dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

const int DIR_NUM = 4;

std::string toString(Dir dir);
void toDelta(Dir dir, int& delta_x, int& delta_y);
Dir dirRotateLeft(Dir dir);
Dir dirRotateRight(Dir dir);

//Robot

class Robot
{
public:
	void initTableSize(int _w, int _h);
	void place(int _x, int _y, Dir _dir);
	void move();
	void rotateLeft();
	void rotateRight();
	std::string report();

protected:
	bool table_inited = false;
	int table_w;
	int table_h;
	int x;
	int y;
	Dir dir;
};
