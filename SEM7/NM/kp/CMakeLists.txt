cmake_minimum_required(VERSION 3.22)
project(CourseProject)

set(CMAKE_CXX_STANDARD 23)


find_package(Qt6 COMPONENTS Widgets Charts DataVisualization REQUIRED)

add_executable(CourseProject CourseProject.cpp Galerkin.cpp)
target_link_libraries(CourseProject PRIVATE Qt6::Widgets Qt6::Charts Qt6::DataVisualization)