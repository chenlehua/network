add_executable(stream_srv server.c)
target_link_libraries(stream_srv network)

add_executable(stream_cli client.c)
target_link_libraries(stream_cli network)