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

std::string dirToString(Dir dir);
Dir stringToDir(std::string s_dir);
void toDelta(Dir dir, int& delta_x, int& delta_y);
Dir dirRotateLeft(Dir dir);
Dir dirRotateRight(Dir dir);

//Robot
class IRobot
{
public:
	virtual void initTableSize(int _w, int _h) = 0;
	virtual void place(int _x, int _y, Dir _dir) = 0;
	virtual bool move() = 0;
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;
	virtual std::string report() const = 0;
	virtual bool isReady() const = 0;
};

class Robot : public IRobot
{
public:
	virtual void initTableSize(int _w, int _h);
	virtual void place(int _x, int _y, Dir _dir);
	virtual bool move();
	virtual void rotateLeft();
	virtual void rotateRight();
	virtual std::string report() const;
	virtual bool isReady() const;

protected:
	bool table_inited = false;
	bool is_placed = false;
	int table_w;
	int table_h;
	int x;
	int y;
	Dir dir;
};

//Controller
class RobotController
{
public:
	RobotController(IRobot& _robot) : robot(_robot){}
	void processCommand(std::string command);
protected:
	IRobot& robot;
};
