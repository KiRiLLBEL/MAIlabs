cmake_minimum_required(VERSION 3.28)
project(NMlab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(NMlab2_1_iter 2_1_iter.cpp
        Solving_methods.h)
add_executable(NMlab2_1_newton 2_1_newton.cpp
        Solving_methods.h)
