cmake_minimum_required(VERSION 3.22)
project(lab6)

set(CMAKE_CXX_STANDARD 23)


find_package(Qt6 COMPONENTS Widgets Charts DataVisualization REQUIRED)

add_executable(NMlab6 NMlab6.cpp hyperbolic.cpp)
target_link_libraries(NMlab6 PRIVATE Qt6::Widgets Qt6::Charts Qt6::DataVisualization)