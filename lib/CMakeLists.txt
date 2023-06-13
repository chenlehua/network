set(network_lib read.c log.c ../grace/grace_server.c ../grace/grace_client.c ../keepalive/keepalive_server.c ../keepalive/keepalive_client.c ../keepalive/message_object.h)

add_library(network ${network_lib})

install(TARGETS network DESTINATION lib)