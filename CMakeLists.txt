cmake_minimum_required(VERSION 3.14)
project(aapp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++-6)

# openmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp")


add_executable(aapp test.cpp
        core_types.h
        naive.h
        boyer_moore.h
        rabin_karp_3.h
        utils.h
        galil_seiferas.h
        test_utils.h
        string_matcher.h
        rabin_karp_2.h
        rabin_karp_1.h
        boyer_moore_simple.h)