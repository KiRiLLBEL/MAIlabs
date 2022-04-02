cmake_minimum_required(VERSION 3.21)
project(NeuralStart)

set(CMAKE_CXX_STANDARD 23)

add_executable(NeuralStart main.cpp)
include_directories("C:/Users/kiril/Projects/clion/NeuralTest/NeuralLib")
target_link_libraries(NeuralStart NeuralLib)

