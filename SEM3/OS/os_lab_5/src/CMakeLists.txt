include_directories(include)

add_executable(main1 main1.c)
add_executable(main2 main2.c)

add_subdirectory(include)

target_link_libraries(main1 der1)
target_link_libraries(main1 trans1)
