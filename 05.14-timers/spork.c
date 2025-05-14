#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* NOTE: For the sake of simplicity, we'll assume that the user will never try
 *       to spork more than one child at a time -- in order to support multiple
 *       children, we'd need some sort of dynamically allocated data structure
 *       to contain multiple child PIDs. */
pid_t pid;

void handler(int signum) {
    kill(pid, SIGKILL);
}

/* spork: Creates a new resource-limited process. */
pid_t spork(time_t timeout) {
    struct rlimit limit;
    struct sigaction action;
    struct itimerval timer;

    if ((pid = fork()) == 0) {
        /* NOTE: In the child, lower the soft and hard limits on the number of
         *       processes to 1, so that the child cannot fork off any children
         *       of its own. */
        getrlimit(RLIMIT_NPROC, &limit);
        limit.rlim_cur = 1;
        limit.rlim_max = 1;
        setrlimit(RLIMIT_NPROC, &limit);
    }
    else {
        /* NOTE: Install a handler for SIGALRM; note that this must be done
         *       before setting the timer, as there is otherwise theoretically
         *       a chance that the timer could go off before we get a chance to
         *       finish installing the signal handler. */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* NOTE: Initialize a timer to go off in timeout seconds... */
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;

        /* NOTE: ...but don't repeat the timer after it elapses... */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;

        /* NOTE: ...and set the timer: */
        setitimer(ITIMER_REAL, &timer, NULL);

        /* NOTE: This "busy waiting" is inefficient and is considered extremely
         *       poor form; if we have nothing to do while we await a signal,
         *       then we should call "pause" instead.
         * while (1); */
    }

    return pid;
}
