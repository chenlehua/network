#ifndef NETWORK_COMMON_H
#define NETWORK_COMMON_H

#include "config.h"
#include    <strings.h>
#include    <string.h>
#include    <unistd.h>
#include    <errno.h>
#include    <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include    <netinet/in.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include    <poll.h>
#include    <fcntl.h>        /* for nonblocking */
#include    <signal.h>
#include <sys/wait.h>
#include    <pthread.h>
#include    <sys/uio.h>        /* for iovec{} and readv/writev */



#define    SERV_PORT      43211
#define    LISTEN_Q        1024
#define    MAX_LINE        4096


size_t read_n(int fd, void *buffer, size_t size);

size_t read_message(int fd, char *buffer, size_t length);

void error(int status, int err, char *fmt, ...);

int tcp_server(int port);

int tcp_client(char *address, int port);

size_t readline(int fd, char *buffer, size_t length);

int tcp_server_listen(int port);

int tcp_nonblocking_server_listen(int port);

void make_nonblocking(int fd);



#endif //NETWORK_COMMON_H
