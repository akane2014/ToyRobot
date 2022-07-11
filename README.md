# ToyRobot

## Get started with ToyRobot

### Tested on Windows 10 with:

Visual Studio Community 2017/2019

cmake 3.24.0

### Tested on Ubuntu 20.04 with:

gcc 8.4.0

cmake 3.16.3

### Build and run steps

#### 1. git clone https://github.com/akane2014/ToyRobot

#### 2. Standard cmake build steps

```
❯ cd ToyRobot
❯ mkdir build
❯ cd build
❯ cmake ..
❯ cmake --build .
```

#### 3. Run the ToyRobot program

ToyRobot needs a filename as an input parameter to indicate where to find the commands you want to execute.
An example run on Windows:
```
❯ ./Debug/ToyRobot ../tests/commands_a.txt
❯ 0,1,NORTH
```
On Ubuntu:
```
❯ ./ToyRobot ../tests/commands_a.txt
❯ 0,1,NORTH
```

#### 4. Run unit/integration tests

On Windows:
```
❯ ./Debug/ToyRobotTest
```

On Ubuntu:
```
❯ ./ToyRobotTest
```

## Some of the decisions I made

### 1. Test driven development

I tried TDD for this project and it's fun. So some implementation might not be optimal but good enough for the current requirements. One example is I put the table size as a member of the Robot class.

### 2. Single header/source file

Since it's quite a small program, I combined all declaration/definition into a single pair of head/souce files:
```
./include/ToyRobot.h
./src/ToyRobot.cpp
```
It's mainly to make it easier to browse if we are going to review it. It could be separated into Utils/Robot/Controller based on the tags I put in the code.
