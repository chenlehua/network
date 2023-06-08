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