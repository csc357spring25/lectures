#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addrs, *addr;

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       server, which requires knowing the server's address. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* NOTE: AF_INET indicates IPv4 (as opposed to IPv6) and SOCK_STREAM
     *       indicates TCP (as opposed to UDP) which are likely the common
     *       sense options as of this writing. */
    getaddrinfo(argv[1], argv[2], &hints, &addrs);

    /* NOTE: getaddrinfo returns a linked list of addresses that could be used
     *       to connect to the indicated hostname; typically we then need to
     *       iterate over that list and try each address. */
    addr = addrs;

    while (addr != NULL) {
        uint32_t ipaddr = ntohl(
         ((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

        printf("%d.%d.%d.%d\n",
         (ipaddr & 0xFF000000) >> 24,
         (ipaddr & 0x00FF0000) >> 16,
         (ipaddr & 0x0000FF00) >> 8,
         (ipaddr & 0x000000FF) >> 0);

        addr = addr->ai_next;
    }

    /* NOTE: None of this establishes a connection or even guarantees than a
     *       connection would be accepted; it just provides the information
     *       necessary to attempt a connection. */

    freeaddrinfo(addrs);
    return EXIT_SUCCESS;
}
