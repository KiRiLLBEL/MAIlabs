cmake_minimum_required(VERSION 3.21)
project(zaychev C)

set(CMAKE_C_STANDARD 99)

add_executable(zaychev main.c queue.c queue.h)
