set(network_lib read.c log.c tcp_server.c tcp_client.c tcp_server.h event_loop.h channel.h event_dispatcher.h channel_map.h acceptor.h tcp_connection.h thread_pool.h event_loop_thread.h buffer.h event_loop.c channel_map.c log.h poll_dispatcher.c epoll_dispatcher.c channel.c utils.h utils.c acceptor.c thread_pool.c event_loop_thread.c tcp_connection.c buffer.c)

add_library(network ${network_lib})

install(TARGETS network DESTINATION lib)