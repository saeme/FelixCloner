cmake_minimum_required(VERSION 3.16)
project(Felix)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

include_directories(include)

add_executable(felix_cloner src/main.cpp src/felix.cpp src/matrix.cpp src/utils.cpp)

# Add the tests subdirectory
add_subdirectory(tests)