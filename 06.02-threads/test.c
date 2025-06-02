#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 256

typedef struct Arg {
    int *arr;
    int n;
} Arg;

int intcmp(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

void *f(void *ptr) {

    /* NOTE: Since the function passed to pthreads must take a void pointer and
     *       return a void pointer, we have to wrap qsort in a helper function
     *       that is compatible with pthreads. */

    Arg *arg = (Arg *)ptr;
    qsort(arg->arr, arg->n, sizeof(int), intcmp);

    return NULL;
}

int main(void) {
    int arr[LENGTH], i;

    /* NOTE: Unlike process IDs, thread IDs are not guaranteed to be integers,
     *       and there is no portable way of printing them out. */

    pthread_t tids[2];
    Arg args[2];

    for (i = 0; i < LENGTH; i++) {
        arr[i] = rand() % 10;
    }

    /* NOTE: This creates two new threads for which f is essentially the "main"
     *       function; when each thread is created, f will be called; once f
     *       returns, the corresponding thread will be terminated. */

    args[0].arr = arr;
    args[0].n = LENGTH / 2;
    pthread_create(&tids[0], NULL, f, &args[0]);

    args[1].arr = arr + (LENGTH / 2);
    args[1].n = LENGTH / 2;
    pthread_create(&tids[1], NULL, f, &args[1]);

    /* NOTE: Since the pthread library has no way of knowing f's signature
     *       ahead of time, f must take as argument a void pointer (see above)
     *       and return a void pointer. If we cared to know the return value,
     *       we could pass a void double pointer below. */

    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);

    for (i = 0; i < LENGTH; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return EXIT_SUCCESS;
}
