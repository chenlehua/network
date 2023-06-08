add_executable(b_server buffer_server.c)
target_link_libraries(b_server network)

add_executable(b_client buffer_client.c)
target_link_libraries(b_client network)