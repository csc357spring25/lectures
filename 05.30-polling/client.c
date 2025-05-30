#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, n;
    char buf[4];

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       server, which requires knowing the server's address and port. For
     *       simplicity, we'll assume that the first address always works. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(argv[1], argv[2], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    connect(fd, addr->ai_addr, addr->ai_addrlen);
    while ((n = read(STDIN_FILENO, buf, 4)) > 0) {
        int i = 0;

        while (i < n) {
            i += write(fd, buf + i, n - i);
        }
    }

    freeaddrinfo(addr);
    close(fd);

    return EXIT_SUCCESS;
}
