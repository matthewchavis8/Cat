cmake_minimum_required(VERSION 3.28)

project(Cat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Cat
    main.cpp
    include/Cat.cpp
    include/Cat.hpp
    include/args.cpp
    include/args.hpp
)