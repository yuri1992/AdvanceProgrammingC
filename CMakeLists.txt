cmake_minimum_required(VERSION 3.3)
project(advancedPrograming)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall -pedantic -Wvla -std=c99")
#include_directories("${YOUR_DIRECTORY} task1")
#include_directories("${YOUR_DIRECTORY} helpers")
set(SOURCE_FILES task5/q3/Q3A/Q3A.c task5/q3/Q3A/Q3A.h task5/q3/Q3A/main.c)

add_executable(advancedPrograming ${SOURCE_FILES} task5/q3/Q3A/main.c)