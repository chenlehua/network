add_executable(r_server01 reliable_server01.c)
target_link_libraries(r_server01 network)

add_executable(r_client01 reliable_client01.c)
target_link_libraries(r_client01 network)

add_executable(r_server02 reliable_server02.c)
target_link_libraries(r_server02 network)

add_executable(r_client02 reliable_client02.c)
target_link_libraries(r_client02 network)