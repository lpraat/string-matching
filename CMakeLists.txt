cmake_minimum_required(VERSION 3.14)
project(aapp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++-6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp")

include_directories(src)

add_executable(aapp test/test.cpp)