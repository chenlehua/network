add_executable(ssh_server ssh_server.c)
target_link_libraries(ssh_server network)

add_executable(ssh_client ssh_client.c)
target_link_libraries(ssh_client network)