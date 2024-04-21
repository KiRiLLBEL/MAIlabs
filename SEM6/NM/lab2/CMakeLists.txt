cmake_minimum_required(VERSION 3.28)
project(NMlab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(NMlab2_1 2_1.cpp Solving_methods.h)
add_executable(NMlab2_2 2_2.cpp Solving_methods.h ../lab1/Matrix.h)
