#include "lib/common.h"

static int count;

static void sig_int(int sig_no) {
    printf("\nsig_int received %d datagrams\n", count);
    exit(0);
}

static void sig_pipe(int sig_no) {
    printf("\nsig_pipe received %d datagrams\n", count);
    exit(0);
}

int main(int argc, char **argv) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    int rt1 = bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (rt1 < 0) {
        error(1, errno, "bind failed ");
    }

    int rt2 = listen(listen_fd, LISTEN_Q);
    if (rt2 < 0) {
        error(1, errno, "listen failed ");
    }

    signal(SIGINT, sig_int);
    signal(SIGPIPE, sig_pipe);

    int conn_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    if ((conn_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_len)) < 0) {
        error(1, errno, "bind failed ");
    }

    char message[MAX_LINE];
    count = 0;

    for (;;) {
        long n = read(conn_fd, message, MAX_LINE - 1);
        if (n < 0) {
            error(1, 0, "error read");
        } else if (n == 0) {
            error(1, 0, "client closed \n");
        }
        message[n] = 0;
        printf("received %ld bytes: %s\n", n, message);
        count++;

        char send_line[MAX_LINE + 3];
        sprintf(send_line, "Hi,%s", message);

        sleep(5);

        long write_nc = send(conn_fd, send_line, strlen(send_line), 0);
        printf("send bytes: %ld \n", write_nc);
        if (write_nc < 0) {
            error(1, errno, "error write");
        }
    }

}