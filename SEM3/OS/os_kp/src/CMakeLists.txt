add_subdirectory(include)
add_executable(main main.c)

target_link_libraries(main list_alloc)
target_link_libraries(main mkk_alloc)
