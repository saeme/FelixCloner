# Specify the minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Define the project name (optional, as it's already defined in the root CMakeLists.txt)
project(Test)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Google Test package
find_package(GTest REQUIRED)

# Enable testing
enable_testing()

# Add the test executable
add_executable(tests test.cpp ../src/felix.cpp ../src/matrix.cpp)

# Include directories for the test executable
target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS} ../include)

# Link Google Test libraries
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main pthread)

# Add the test to the project
add_test(NAME FelixTests COMMAND tests)