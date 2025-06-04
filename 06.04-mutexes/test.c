#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 8192

typedef struct Arg {
    int x;
    int *arr;
    int n;
} Arg;

/* NOTE: Since threads share the same data segment, we can simply have each
 *       thread increment the same global counter... */
int count = 0;

/* NOTE: ...however, this creates a race condition where two threads could try
 *       to increment the counter at the same time. */
pthread_mutex_t lock;

void *f(void *ptr) {
    Arg *arg = (Arg *)ptr;
    int i;

    for (i = 0; i < arg->n; i++) {
        if (arg->arr[i] == arg->x) {
            pthread_mutex_lock(&lock);

            /* NOTE: By definition, a mutex can only be possessed by one thread
             *       at any given time. If we get here, we must have the mutex,
             *       which means no one else has the mutex, which means no one
             *       else is trying to execute the following code. */

            count++;
            pthread_mutex_unlock(&lock);
        }
    }

    return NULL;
}

int main(void) {
    int arr[LENGTH], i;
    pthread_t tids[2];
    Arg args[2];

    for (i = 0; i < LENGTH; i++) {
        arr[i] = rand() % 10;
    }

    args[0].x = 1;
    args[0].arr = arr;
    args[0].n = LENGTH / 2;
    args[1].x = 1;
    args[1].arr = arr + (LENGTH / 2);
    args[1].n = LENGTH / 2;

    pthread_mutex_init(&lock, NULL);
    pthread_create(&tids[0], NULL, f, &args[0]);
    pthread_create(&tids[1], NULL, f, &args[1]);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_mutex_destroy(&lock);

    printf("%d\n", count);
    return EXIT_SUCCESS;
}
