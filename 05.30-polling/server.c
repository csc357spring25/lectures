#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, client, n;
    char buf[5];

    /* NOTE: This program, the server, will passively run on one computer and
     *       wait for clients to establish connections via our address. For
     *       simplicity, we'll assume that the first address always works. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, argv[1], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    client = accept(fd, NULL, NULL);
    while ((n = read(client, buf, 4)) > 0) {
        write(STDOUT_FILENO, buf, n);
    }

    freeaddrinfo(addr);
    close(client);
    close(fd);

    return EXIT_SUCCESS;
}
