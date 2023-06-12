#ifndef NETWORK_COMMON_H
#define NETWORK_COMMON_H

#include    <strings.h>
#include    <unistd.h>
#include    <errno.h>
#include    <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include    <netinet/in.h>
#include <arpa/inet.h>
#include <stdarg.h>


#define    SERV_PORT      43211
#define    LISTEN_Q        1024
#define    MAX_LINE        4096


size_t read_n(int fd, void *buffer, size_t size);

void error(int status, int err, char *fmt, ...);

#endif //NETWORK_COMMON_H
