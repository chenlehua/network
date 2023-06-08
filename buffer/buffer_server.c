#include "lib/common.h"

void read_data(int sock_fd) {
    char buf[1024];

    int time = 0;

    for (;;) {
        fprintf(stdout, "block in read \n");
        if (read_n(sock_fd, buf, 1024) == 0)
            return;

        time++;

        fprintf(stdout, "1k read for %d \n", time);
        usleep(1000000);
    }
}

int main(int argc, char **argv) {
    socklen_t cli_len;
    struct sockaddr_in cli_addr, serv_addr;

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(12345);

    int r = bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (r != 0) {
        fprintf(stdout, "bind error");
        return r;
    }
    listen(listen_fd, 1024);


    for (;;) {
        cli_len = sizeof(cli_addr);
        int conn_fd = accept(listen_fd, (struct sockaddr *) &cli_addr, &cli_len);
        read_data(conn_fd);
        close(conn_fd);
    }
}