# ToyRobot

## Run The Project on Windows

Requirement:
Visual Studio Community 2017
cmake (version > 3.5)

1. Standard cmake build steps

```
❯ mkdir build
❯ cd build
❯ cmake .. -G "Visual Studio 15 2017" -A x64
```

2. Open ToyRobot.sln with Visual Studio Community 2017 and build the solution

3. Run the ToyRobot program 

It is located in ./build/Debug(or Release)/ToyRobot.exe and needs a filename as an input parameter to indicate where to find the commands you want to execute.
An example run would be like:
```
❯ ./build/Debug/ToyRobot ./tests/commands_a.txt
❯ 0,1,NORTH
```

## Run the Project on Linux
