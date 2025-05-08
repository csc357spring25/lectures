#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int i, status = EXIT_FAILURE, tmp;
    pid_t pid;

    for (i = 2; i < argc; i++) {
        if ((pid = fork()) == 0) {
            status = fsearch(argv[i], argv[1]);
            exit(status);
        }
    }

    for (i = 2; i < argc; i++) {
        pid = wait(&tmp);
        if (WIFEXITED(tmp)) {
            status = status && WEXITSTATUS(tmp);
        }
    }

    return status;
}

/* fsearch: Prints occurrences of a string in a file. */
int fsearch(char *fname, char *str) {
    int status = EXIT_FAILURE;
    char buf[LINELEN];
    FILE *file = fopen(fname, "r");

    while (fgets(buf, LINELEN, file) != NULL) {
        if (strstr(buf, str) != NULL) {
            printf("%s: %s", fname, buf);
            status = EXIT_SUCCESS;
        }
    }

    fclose(file);
    return status;
}
