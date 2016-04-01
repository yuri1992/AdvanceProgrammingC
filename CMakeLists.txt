cmake_minimum_required(VERSION 3.3)
project(advancedPrograming)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall -pedantic -Wvla -std=c99")
include_directories("${YOUR_DIRECTORY} task1")
include_directories("${YOUR_DIRECTORY} helpers")
#set(SOURCE_FILES helpers/text.c)
set(SOURCE_FILES task2/Q1_B.c)

add_executable(advancedPrograming ${SOURCE_FILES} task2/Q1_B.c)