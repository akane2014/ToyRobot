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

