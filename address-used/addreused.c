//
// Created by chenlehua on 2023/9/1.
//

#include "lib/common.h"

static int count;

static void sig_int(int signo) {
    printf("\nreceived %d datagram\n", count);
    exit(0);
}

int main(int argc, char **argv) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    int on = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    int rt1 = bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (rt1 < 0) {
        error(1, errno, "bind failed ");
    }

    int rt2 = listen(listen_fd, LISTEN_Q);
    if (rt2 < 0) {
        error(1, errno, "listen failed ");
    }

    signal(SIGPIPE, SIG_IGN);

    int connfd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    if ((connfd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_len)) < 0) {
        error(1, errno, "accept failed ");
    }

    char message[MAX_LINE];
    count = 0;

    for (;;) {
        int n = read(connfd, message, MAX_LINE);
        if (n < 0) {
            error(1, errno, "error read ");
        } else if (n == 0) {
            error(1, 0, "client closed \n ");
        }
        message[n] = 0;
        printf("received %d bytes: %s\n", n, message);
        count++;
    }

}