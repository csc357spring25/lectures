#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "spork.h"

int main(void) {
    int status;
    pid_t pid;

    if ((pid = spork(5)) == 0) {
        printf("%ld is the child of %ld.\n", (long)getpid(), (long)getppid());

        while (1) {
            fork();
            perror("fork");
            sleep(1);
        }
    }
    else {
        printf("%ld is the parent of %ld.\n", (long)getpid(), (long)pid);
        pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("%ld exited status %d.\n", (long)pid, WEXITSTATUS(status));
        }
        else {
            printf("%ld terminated abnormally.\n", (long)pid);
        }
    }

    return 0;
}
