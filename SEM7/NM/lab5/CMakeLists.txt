cmake_minimum_required(VERSION 3.22)
project(lab5)

set(CMAKE_CXX_STANDARD 23)


add_subdirectory(matplotplusplus)

add_executable(NMlab5 NMlab5.cpp parabolic.cpp)
# target_link_libraries(
#     NMlab5
#     PRIVATE ${Python3_LIBRARIES}
# )
target_link_libraries(NMlab5 PUBLIC matplot)
