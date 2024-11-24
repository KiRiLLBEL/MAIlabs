cmake_minimum_required(VERSION 3.22)
project(lab5)

set(CMAKE_CXX_STANDARD 23)


find_package(Qt6 COMPONENTS Widgets Charts DataVisualization REQUIRED)

add_executable(NMlab5 NMlab5.cpp parabolic.cpp)
target_link_libraries(NMlab5 PRIVATE Qt6::Widgets Qt6::Charts Qt6::DataVisualization)