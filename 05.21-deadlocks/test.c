#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXLEN 81

int main(void) {
    int ptoc[2], ctop[2];

    /* NOTE: In theory, this could be done with a single pipe, as long as we
     *       were careful about timing which process read and which process
     *       wrote and when, but in general it's a whole lot easier to just
     *       make two pipes, one for each direction: */

    pipe(ptoc);
    pipe(ctop);

    if (!fork()) {
        /* NOTE: By replacing stdin and stdout with the read end of the
         *       parent-to-child pipe and the write end of the child-to-parent
         *       pipe, we can trick the child into communicating with the
         *       parent through ordinary I/O functions: */

        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

        /* NOTE: Now that the relevant ends of the pipes are attached to the
         *       existing stdin/stdout streams, we don't need any of the actual
         *       pipe file descriptors anymore; we should close them to avoid
         *       tricking anyone into thinking there's more data coming. */

        close(ptoc[0]);
        close(ptoc[1]);
        close(ctop[0]);
        close(ctop[1]);

        execlp("./hello", "./hello", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    }
    else {
        char buf[MAXLEN];

        close(ptoc[0]);
        close(ctop[1]);

        /* NOTE: The parent must write before attempting to read; if it reads
         *       first, the parent and child will be deadlocked: they will both
         *       blocked attempting to read data that the other will later
         *       write. */

        write(ptoc[1], "parent\n", 7);
        close(ptoc[1]);

        read(ctop[0], buf, MAXLEN);
        close(ctop[0]);

        printf("Child printed:\n%s", buf);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
