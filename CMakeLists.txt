cmake_minimum_required(VERSION 3.5)

project(ToyRobot)

########################################
# Set up the compiler flags
########################################
set(CMAKE_CXX_STANDARD 14)

########################################
# Get googletest
########################################
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

########################################
# Define include directories
########################################
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

add_library(ToyRobot_lib src/ToyRobot.cpp)
add_executable(ToyRobot src/main.cpp)
target_link_libraries(ToyRobot ToyRobot_lib)

enable_testing()

add_executable(
  ToyRobotTest
  tests/ToyRobotTest.cpp
)

target_link_libraries(ToyRobotTest gtest_main gmock_main)
target_link_libraries(ToyRobotTest ToyRobot_lib)

include(GoogleTest)
gtest_discover_tests(ToyRobotTest)
