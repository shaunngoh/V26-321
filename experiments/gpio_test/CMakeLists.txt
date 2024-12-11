# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(PigpioButtonExample C)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Include pigpio library
find_library(PIGPIO_LIB pigpio REQUIRED)
find_library(RT_LIB rt REQUIRED)

# Add executable
add_executable(button_example main.c)

# Link libraries to the executable
target_link_libraries(button_example PRIVATE ${PIGPIO_LIB} ${RT_LIB})