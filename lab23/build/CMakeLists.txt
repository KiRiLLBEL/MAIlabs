cmake_minimum_required(VERSION 3.21)
project(MainBuild)

set(CMAKE_C_STANDARD 99)

add_executable(MainBuild main.c)
include_directories("C:/Users/kiril/Projects/lab23/nodeLibrary")
target_link_libraries(MainBuild nodeLibrary)

