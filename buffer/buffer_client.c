

#include "lib/common.h"


#define  MESSAGE_SIZE 1024000

void send_data(int sock_fd) {
    char *query;
    query = malloc(MESSAGE_SIZE + 1);

    for (int i = 0; i < MESSAGE_SIZE; i++) {
        query[i] = 'a';
    }
    query[MESSAGE_SIZE] = '\0';

    const char *cp;
    cp = query;
    size_t remaining = strlen(query);
    while (remaining) {
        long n_written = send(sock_fd, cp, remaining, 0);
        fprintf(stdout, "send into buffer %ld \n", n_written);
        if (n_written <= 0) {
            error(1, errno, "send failed");
        }
        remaining -= n_written;
        cp += n_written;
    }
}

int main(int argc, char **argv) {
    struct sockaddr_in serv_addr;

    if (argc != 2)
        error(1, 0, "usage: b_client <IPaddress>");

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
    int connect_rt = connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (connect_rt < 0) {
        error(1, errno, "connect failed");
    }
    send_data(sock_fd);
    exit(0);
}