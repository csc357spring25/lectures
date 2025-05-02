#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    if (stat(argv[1], &buf) < 0) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    /* NOTE: Each file is uniquely identified by a (device, inode) number pair;
     *       files do *not* have names! Their names are mapped to their inode
     *       numbers by their parent directories, and the name is not part of
     *       the information returned by stat. */

    printf("%s:\n", argv[1]);
    printf("    Device number:    %ld\n", (long)buf.st_dev);
    printf("    Inode number:     %ld\n", (long)buf.st_ino);
    printf("    Size in bytes:    %ld\n", (long)buf.st_size);
    printf("    Number of blocks: %ld\n", (long)buf.st_blocks);

    return EXIT_SUCCESS;
}
