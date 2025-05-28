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
     *       wait for other programs, the clients, to establish connections. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /* NOTE: For simplicity, we'll assume that the first address will always
     *       work instead of iterating over the list of addresses. */

    getaddrinfo(NULL, argv[1], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    /* NOTE: The server must bind its socket to a specific port, on which it
     *       will then listen for new incoming connections. */

    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    /* NOTE: If we cared to know the client's address, we could pass pointers
     *       to structures which would be populated by accept. */

    client = accept(fd, NULL, NULL);

    /* NOTE: This creates a new socket for communication with the accepted
     *       client; the existing socket can continue to be used to listen for
     *       new incoming connections. */

    while ((n = read(client, buf, 4)) > 0) {
        buf[n] = '\0';
        printf("Client sent \"%s\".\n", buf);
    }

    freeaddrinfo(addr);
    close(client);
    close(fd);

    return EXIT_SUCCESS;
}
