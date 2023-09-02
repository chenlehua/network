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

char *run_cmd(char *cmd) {
    char *data = malloc(16384);
    bzero(data, sizeof(data));
    FILE *fdp;
    const int max_buffer = 256;
    char buffer[max_buffer];
    fdp = popen(cmd, "r");
    char *data_index = data;
    if (fdp) {
        while (!feof(fdp)) {
            if (fgets(buffer, max_buffer, fdp) != NULL) {
                int len = strlen(buffer);
                memcpy(data_index, buffer, len);
                data_index += len;
            }
        }
        pclose(fdp);
    }

    return data;
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

    signal(SIGINT, sig_int);
    signal(SIGPIPE, sig_pipe);

    int conn_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    char buf[256];
    count = 0;

    while (1) {
        if ((conn_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_len)) < 0) {
            error(1, errno, "bind failed ");
        }

        for (;;) {
            bzero(buf, sizeof(buf));
            long n = read(conn_fd, buf, sizeof(buf) - 1);
            if (n < 0) {
                error(1, 0, "error read message");
            } else if (n == 0) {
                printf("client closed \n");
                close(conn_fd);
                break;
            }

            buf[n] = 0;
            printf("received %ld bytes: %s\n", n, buf);
            count++;

            if (strncmp(buf, "ls", n) == 0) {
                char *result = run_cmd("ls");
                if (send(conn_fd, result, strlen(result), 0) < 0) {
                    return 1;
                }
                free(result);
            } else if (strncmp(buf, "pwd", n) == 0) {
                char buffer[256];
                char *result = getcwd(buffer, 256);
                if (send(conn_fd, result, strlen(result), 0) < 0)
                    return 1;
            } else if (strncmp(buf, "cd ", 3) == 0) {
                char target[256];
                bzero(target, sizeof(target));
                memcpy(target, buf + 3, strlen(buf) - 3);
                if (chdir(target) == -1) {
                    printf("change dir failed, %s\n", target);
                }
            } else {
                char *error = "error: unknown input type";
                if (send(conn_fd, error, strlen(error), 0) < 0)
                    return 1;
            }
        }
    }
    exit(0);
}