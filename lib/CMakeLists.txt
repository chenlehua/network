set(network_lib read.c log.c)

add_library(network ${network_lib})

install(TARGETS network DESTINATION lib)