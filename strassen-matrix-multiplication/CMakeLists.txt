cmake_minimum_required(VERSION 3.10)

# Set the project name
project(StrassenMatrixMultiplication)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(src)

# Add the executable
add_executable(StrassenMatrixMultiplication src/main.cpp src/matrix.cpp src/strassen.cpp)

# Add tests
enable_testing()
add_subdirectory(tests)