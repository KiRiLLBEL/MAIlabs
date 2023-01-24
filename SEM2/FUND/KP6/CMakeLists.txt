cmake_minimum_required(VERSION 3.21)
project(KP6 C)

set(CMAKE_C_STANDARD 99)

add_executable(count count.c table.c)
add_executable(print print.c table.c)
add_executable(generate generate.c table.c)
add_executable(input input.c table.c)
