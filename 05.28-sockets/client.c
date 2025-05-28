#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, i = 0;
    char buf[15] = "Hello, server!";

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       server, which requires knowing the server's address and port. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* NOTE: For simplicity, we'll assume that the first address will always
     *       work instead of iterating over the list of addresses. */

    getaddrinfo(argv[1], argv[2], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    /* NOTE: It is possible that the entire buffer cannot be written at once,
     *       in which case we have to pick up where we left off. */

    connect(fd, addr->ai_addr, addr->ai_addrlen);
    while (i < 14) {
        i += write(fd, buf + i, 14 - i);
    }

    freeaddrinfo(addr);
    close(fd);

    return EXIT_SUCCESS;
}
