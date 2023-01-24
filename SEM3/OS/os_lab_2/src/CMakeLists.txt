include_directories(errorlib)

add_executable(main main.c)
add_executable(child1 child1.c)
add_executable(child2 child2.c)

add_subdirectory(errorlib)

target_link_libraries(main errorlib)
target_link_libraries(child1 errorlib)
target_link_libraries(child2 errorlib)