cmake_minimum_required(VERSION 3.16)

project(Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

# Add the test executable
add_executable(tests test.cpp ../src/felix.cpp ../src/matrix.cpp)

# Link Google Test libraries
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main pthread)

# Add the test to the project
add_test(NAME FelixTests COMMAND tests)