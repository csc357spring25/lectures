#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int src, dest, n;

    /* NOTE: System calls will set the global variable "errno" to indicate
     *       failure; the standard library function "perror" can then be used
     *       to print a human-readable error message to stderr. */

    if ((src = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    if ((dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        perror(argv[2]);
        close(src);
        return EXIT_FAILURE;
    }

    while ((n = read(src, buf, sizeof(char) * 8)) > 0) {
        /* NOTE: If the input does not contain a multiple of 8 characters, then
         *       the last byte has to be padded with zeroes. */
        while (n < 8) {
            buf[n] = '0';
            n++;
        }
        byte = stob(buf);
        write(dest, &byte, sizeof(char) * 1);
    }

    close(src);
    close(dest);

    /* NOTE: Programs should return EXIT_SUCCESS on success and EXIT_FAILURE on
     *       failure, which are most likely but do not necessarily have to be
     *       defined as 0 and 1, respectively. */

    return EXIT_SUCCESS;
}

unsigned char stob(char *bits) {
    unsigned char byte = 0, mask = 0x80;
    int i;

    for (i = 0; i < 8; i++) {
        if (bits[i] == '1') {
            byte |= mask;
        }
        mask >>= 1;
    }

    return byte;
}
