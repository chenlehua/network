set(network_lib read.c log.c ../grace/grace_server.c ../grace/grace_client.c)

add_library(network ${network_lib})

install(TARGETS network DESTINATION lib)