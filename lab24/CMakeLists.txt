cmake_minimum_required(VERSION 3.22)
project(lab24 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab24 main.c lexer.c tree.c transform.c)
