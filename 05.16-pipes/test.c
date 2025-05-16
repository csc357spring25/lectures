#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fds[2];

    /* NOTE: A pipe is essentially a temporary file managed by the OS. This
     *       creates a pipe and attaches two file descriptors: fds[0] will
     *       be the read end, and fds[1] will be the write end. */
    pipe(fds);

    if (!fork()) {
        char buf[5];
        int n;

        close(fds[1]);

        while ((n = read(fds[0], buf, 4)) > 0) {
            buf[n] = '\0';
            printf("%ld read \"%s\" from pipe.\n", (long)getpid(), buf);
        }

        close(fds[0]);
    }
    else {
        /* NOTE: To generalize the below comment, we should always close pipe
         *       ends as soon as we know we don't need them, not only to
         *       release resources that we don't need, but also to ensure that
         *       no other processes are blocked waiting for us to do something
         *       with the pipe. */
        close(fds[0]);

        write(fds[1], "Hello, child!\n", 14);
        printf("%ld wrote \"Hello, child!\\n\" to the pipe.\n", (long)getpid());

        /* NOTE: Unless the parent closes the write end of the pipe, the child
         *       will have no way of knowing that there is no more data coming
         *       in the future. This must be done before waiting for the child,
         *       because the child can't terminate until the parent closes the
         *       write end of the pipe. */
        close(fds[1]);

        wait(NULL);
    }

    return EXIT_SUCCESS;
}
