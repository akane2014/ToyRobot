#pragma once

#include <string>

enum class Dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Robot
{
public:
	void init(int _x, int _y, Dir _dir);
	std::string report();
};
