/* NOTE: This copies the contents of one file into another using standard
 *       library functions, which encapsulate the most common functionality. */
#include <stdio.h>

#define SIZE 16

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n;
    FILE *src, *dest;

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

    /* NOTE: System calls must do more and therefore take longer than ordinary
     *       functions -- fread doesn't avoid calling read, but it will likely
     *       read more bytes than it needs and store them in a buffer behind
     *       the scenes, so that future calls to fread don't have to call read
     *       again, thereby minimizing the number of system calls and thus the
     *       running time of the program. */
    while ((n = fread(buf, sizeof(char), SIZE, src)) > 0) {
        fwrite(buf, sizeof(char), n, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}
