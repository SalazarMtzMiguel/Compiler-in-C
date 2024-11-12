cmake_minimum_required(VERSION 3.10)
project(Compiler)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.c")

# Add the executable
add_executable(compiler ${SOURCES})