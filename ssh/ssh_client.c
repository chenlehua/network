#include "lib/common.h"

#define  MAXLINE     1024


int main(int argc, char **argv) {
    if (argc != 3) {
        error(1, 0, "usage: tcp_client <IPaddress> <port>");
    }
    int port = atoi(argv[2]);
    int socket_fd = tcp_client(argv[1], port);

    char send_line[MAXLINE], recv_line[MAXLINE + 1];
    long n;

    fd_set read_mask;
    fd_set all_reads;

    FD_ZERO(&all_reads);
    FD_SET(0, &all_reads);
    FD_SET(socket_fd, &all_reads);

    for (;;) {
        read_mask = all_reads;
        int rc = select(socket_fd + 1, &read_mask, NULL, NULL, NULL);
        if (rc <= 0)
            error(1, errno, "select failed");

        if (FD_ISSET(socket_fd, &read_mask)) {
            n = read(socket_fd, recv_line, MAXLINE);
            if (n < 0) {
                error(1, errno, "read error");
            } else if (n == 0) {
                printf("server closed \n");
                break;
            }
            recv_line[n] = 0;
            fputs(recv_line, stdout);
            fputs("\n", stdout);
        }

        if (FD_ISSET(0, &read_mask)) {
            if (fgets(send_line, MAXLINE, stdin) != NULL) {
                int i = strlen(send_line);
                if (send_line[i - 1] == '\n') {
                    send_line[i - 1] = 0;
                }

                if (strncmp(send_line, "quit", strlen(send_line)) == 0) {
                    if (shutdown(socket_fd, 1)) {
                        error(1, errno, "shutdown failed");
                    }
                }

                size_t rt = write(socket_fd, send_line, strlen(send_line));
                if (rt < 0) {
                    error(1, errno, "write failed ");
                }

            }

        }

    }
}