cmake_minimum_required(VERSION 3.22)
project(lab7)

set(CMAKE_CXX_STANDARD 23)


find_package(Qt6 COMPONENTS Widgets Charts DataVisualization REQUIRED)

add_executable(NMlab7 NMlab7.cpp elleptic.cpp)
target_link_libraries(NMlab7 PRIVATE Qt6::Widgets Qt6::Charts Qt6::DataVisualization)