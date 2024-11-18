cmake_minimum_required(VERSION 3.22)
project(lab6)

set(CMAKE_CXX_STANDARD 23)


add_subdirectory(matplotplusplus)

add_executable(NMlab6 NMlab6.cpp hyperbolic.cpp)
target_link_libraries(NMlab6 PUBLIC matplot)
