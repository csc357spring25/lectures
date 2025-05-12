#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* NOTE: A signal handler is called in response to a signal; it is not called
 *       within our code proper. It effectively has no caller, and so it cannot
 *       take additional arguments or produce a return value. Additionally, we
 *       should avoid calling printf, which is not async-signal-safe -- we
 *       usually just want to set some global flag inside of a handler, which
 *       we can then check inside our ordinary code to see if a signal was
 *       received. */
void handler(int signum) {
    if (signum == SIGINT) {
        printf("But VINAYAK lets HIS PROCESSES stay up as long as they want!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But HOLLY lets HER PROCESSES eat clock cycles before dinner!\n");
    }
}

int main(void) {
    struct sigaction action;

    /* NOTE: These are the common-sense options that we typically want when
     *       installing a signal handler: we want to call a function in
     *       response to a signal, restarting any interrupted system calls. */
    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);

    /* NOTE: If we cared to save the existing signal handler -- for example, to
     *       restore it later -- we could pass a pointer to a second structure,
     *       which would be filled with the details of the existing handler. */
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    /* NOTE: The above effectively ignores Ctrl+c (SIGINT) and Ctrl+\ (SIGQUIT),
     *       but a Ctrl+z (SIGSTOP) or a SIGKILL cannot be blocked, ignored, or
     *       otherwise handled. */
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    while (1);

    return EXIT_SUCCESS;
}
