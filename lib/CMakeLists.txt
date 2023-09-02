set(network_lib read.c log.c tcp_server.c tcp_client.c)

add_library(network ${network_lib})

install(TARGETS network DESTINATION lib)