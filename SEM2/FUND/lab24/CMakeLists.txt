cmake_minimum_required(VERSION 3.22)
project(full C)

set(CMAKE_C_STANDARD 99)

add_executable(full main.c transform.c token.c printer.c parser.c mystring.c lexer.c expression.c)
