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

    /* TODO: For Asgn. 5, read in all of the directory entries and make copies
     *       of at least their names, which can then be sorted in alphabetical
     *       order before actually attempting to traverse any of them. */

    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &buf);
        printf("\"%s\" -> %ld (%ld bytes in %ld blocks)\n",
         entry->d_name, (long)entry->d_ino,
         (long)buf.st_size, (long)buf.st_blocks);
    }

    /* TODO: For Asgn. 5, make this functionality recursive: if a directory
     *       entry is itself a directory, recurse on that entry before moving
     *       on to the next entry:
     *
     * while (...) {
     *     ...
     *     if (S_ISDIR(buf.st_mode)) {
     *         chdir(entry->d_name);
     *         ...
     *         chdir("..");
     *     }
     *     ...
     * }
     */

    closedir(dir);

    return EXIT_SUCCESS;
}
