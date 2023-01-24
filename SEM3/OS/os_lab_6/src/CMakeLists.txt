add_subdirectory(library)
add_executable(client client.c)
add_executable(server server.c)


set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
target_link_libraries(client zmq)
target_link_libraries(server zmq)
target_link_libraries(client zmq_s)
target_link_libraries(server zmq_s)	