#include "common.h"


size_t read_n(int fd, void *buffer, size_t size) {
    char *buffer_pointer = buffer;
    size_t length = size;

    while (length > 0) {
        long result = read(fd, buffer_pointer, length);

        if (result < 0) {
            if (errno == EINTR)
                continue;
            else
                return -1;
        } else if (result == 0)
            break;

        length -= result;
        buffer_pointer += result;
    }
    return (size - length);
}

size_t read_message(int fd, char *buffer, size_t length) {
    u_int32_t msg_length;
    u_int32_t msg_type;
    int rc;


    rc = read_n(fd, (char *) &msg_length, sizeof(u_int32_t));
    if (rc != sizeof(u_int32_t))
        return rc < 0 ? -1 : 0;
    msg_length = ntohl(msg_length);

    rc = read_n(fd, (char *) &msg_type, sizeof(msg_type));
    if (rc != sizeof(u_int32_t))
        return rc < 0 ? -1 : 0;

    if (msg_length > length) {
        return -1;
    }

    rc = read_n(fd, buffer, msg_length);
    if (rc != msg_length)
        return rc < 0 ? -1 : 0;
    return rc;
}

size_t readline_2(int fd, char *buffer, size_t length) {
    char *buf_first = buffer;

    char c;
    while (length > 0 && recv(fd, &c, 1, 0) == 1) {
        *buffer++ = c;
        length--;
        if (c == '\n') {
            *buffer = '\0';
            return buffer - buf_first;
        }
    }

    return -1;

}


size_t readline(int fd, char *buffer, size_t length) {
    char *buf_first = buffer;
    static char *buffer_pointer;
    int nleft = 0;
    static char read_buffer[512];
    char c;


    while (--length > 0) {
        if (nleft <= 0) {
            int nread = recv(fd, read_buffer, sizeof(read_buffer), 0);
            if (nread < 0) {
                if (errno == EINTR) {
                    length++;
                    continue;
                }
                return -1;
            }
            if (nread == 0)
                return 0;
            buffer_pointer = read_buffer;
            nleft = nread;
        }
        c = *buffer_pointer++;
        *buffer++ = c;
        nleft--;
        if (c == '\n') {
            *buffer = '\0';
            return buffer - buf_first;
        }
    }

    return -1;
}