#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat buf;

    /* NOTE: Error checking has been omitted for brevity, but it would be best
     *       practice to check the return values of all these system calls and
     *       library functions, and call perror if necessary... */

    chdir(argv[1]);
    dir = opendir(".");

    /* NOTE: The order of entries returned by readdir is effectively random,
     *       and the contents of the directory entry it returns will persist
     *       only until readdir is called again. If we want to save those
     *       contents, we have to make our own copy. Additionally, an entry
     *       is only guaranteed to contain a filename and an inode number. If
     *       we need other metadata, we have to call stat instead. */

    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &buf);
        printf("\"%s\" -> %ld (%ld bytes in %ld blocks)\n",
         entry->d_name, (long)entry->d_ino,
         (long)buf.st_size, (long)buf.st_blocks);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}
