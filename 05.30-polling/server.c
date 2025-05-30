#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    struct pollfd clients[17];
    int fd, n, i;

    /* NOTE: This program, the server, will passively run on one computer and
     *       wait for clients to establish connections via our address. For
     *       simplicity, we'll assume that the first address always works. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, argv[1], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 16);

    /* NOTE: For simplicity, we assume we need to be able to handle up to 17
     *       connections simultaneously, 16 clients plus the 1 socket for
     *       accepting new connections. */

    clients[0].fd = fd;
    clients[0].events = POLLIN;
    n = 1;

    while (poll(clients, n, n > 1 ? -1 : 10000) > 0) {

        /* NOTE: Since it is possible that one client might be more important
         *       than others, poll only indicates *how many* clients are ready
         *       for I/O; we have to search for *which* clients those are. */

        for (i = 0; i < n; i++) {
            if (clients[i].revents & POLLIN) {
                if (clients[i].fd == fd) {

                    /* NOTE: If the descriptor that is ready for input is the
                     *       listening socket, we need to accept a client, and
                     *       add it to the array of polled descriptors. */

                    clients[n].fd = accept(fd, NULL, NULL);
                    fcntl(clients[n].fd, F_SETFL, O_NONBLOCK);
                    clients[n].events = POLLIN;
                    n++;
                }
                else {
                    int m;
                    char buf[5];

                    /* NOTE: Otherwise, we need to read data that was sent from
                     *       an existing client. Since the descriptor was made
                     *       non-blocking... */

                    while ((m = read(clients[i].fd, buf, 4)) > 0) {
                        write(STDOUT_FILENO, buf, m);
                    }

                    /* NOTE: ...either m is 0 (meaning the client closed the
                     *       connection), or it is -1 (meaning no data is
                     *       available if errno is set to EAGAIN). */

                    if (m == 0 || errno != EAGAIN) {
                        close(clients[i].fd);
                        clients[i] = clients[n - 1];
                        n--;
                    }
                }
            }
        }
    }

    freeaddrinfo(addr);
    close(fd);

    return EXIT_SUCCESS;
}
