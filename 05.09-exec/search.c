#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int main(int argc, char *argv[]) {
    int i, status = EXIT_FAILURE, tmp;
    pid_t pid;

    for (i = 2; i < argc; i++) {
        if ((pid = fork()) == 0) {
            /* NOTE: The existing grep utility already knows how to search a
             *       file; rather than rewriting that logic; we can replace the
             *       child process with the grep executable.
             * status = fsearch(argv[i], argv[1]); */

            /* NOTE: We must replace the child rather than the parent, because
             *       only the parent knows to wait for the other children. By
             *       convention, the first argument is the executable's name. */
            execlp("grep", "grep", argv[1], argv[i], NULL);

            /* NOTE: Since exec replaces the current process with another
             *       executable, the only way to get this far is if the call to
             *       exec failed. */
            perror("exec");
            exit(EXIT_FAILURE);
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
