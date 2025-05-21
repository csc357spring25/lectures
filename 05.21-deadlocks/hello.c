#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[16];

    /* NOTE: This program expects to use the existing stdin/stdout streams. If
     *       we replace those streams with the read and write ends of a pipe,
     *       respectively, then we can "trick" this program into communicating
     *       with another process instead... */

    fgets(buf, 16, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello, %s!\n", buf);

    return 0;
}
