#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       server, which requires knowing the server's address and port. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(argv[1], argv[2], &hints, &addr);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
