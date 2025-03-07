cmake_minimum_required(VERSION 3.28)

project(Cat)

# setting standard to compile in 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent module to fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Ensure GoogleTest doesn’t override project settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)

enable_testing()

# Main executable
add_executable(Cat
    main.cpp
    include/Cat.cpp
    include/Cat.hpp
    include/args.cpp
    include/args.hpp
)

# Test executable
add_executable(Cat_Tests
    tests/test_Cat.cpp
    tests/test_main.cpp
    include/Cat.cpp
    include/Cat.hpp
)

# Link googletest to tests
target_link_libraries(Cat_Tests
    gtest
    gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(Cat_Tests)
