cmake_minimum_required(VERSION 3.28)
project(NMlab3)

set(CMAKE_CXX_STANDARD 20)
find_package(Python3 3.8.10 EXACT REQUIRED COMPONENTS Interpreter Development NumPy)
add_executable(NMlab3_1 NMlab3_1.cpp Polynoms.h)
add_executable(NMlab3_2 NMlab3_2.cpp Polynoms.h)
add_executable(NMlab3_3 NMlab3_3.cpp Polynoms.h)
add_executable(NMlab3_4 NMlab3_4.cpp Polynoms.h)
add_executable(NMlab3_5 NMlab3_5.cpp Polynoms.h)


target_include_directories(NMlab3_1 PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(NMlab3_1 PRIVATE ${Python3_LIBRARIES})
target_include_directories(NMlab3_2 PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(NMlab3_2 PRIVATE ${Python3_LIBRARIES})
target_include_directories(NMlab3_3 PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(NMlab3_3 PRIVATE ${Python3_LIBRARIES})
target_include_directories(NMlab3_4 PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(NMlab3_4 PRIVATE ${Python3_LIBRARIES})
target_include_directories(NMlab3_5 PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(NMlab3_5 PRIVATE ${Python3_LIBRARIES})

target_include_directories(NMlab3_1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(NMlab3_2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(NMlab3_3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(NMlab3_4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(NMlab3_5 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
