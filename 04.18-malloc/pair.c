#include <stdio.h>
#include <stdlib.h>

int *pair(int, int);

int main(void) {
    int *arr;

    arr = pair(1, 2);

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    return 0;
}

int *pair(int first, int second) {
    /* NOTE: Returning this array is never safe; the array is local, allocated
     *       on the runtime stack, and it will be deallocated as soon as the
     *       function returns, so its address is effectively garbage:
     * int arr[2]; */

    /* NOTE: By instead dynamically allocating space on the heap, we don't need
     *       to know how much space we need at compile-time, and we don't need
     *       to worry that the space will be deallocated on return: */
    int *arr = (int *)malloc(sizeof(int) * 2);

    /* NOTE: Since array and pointer syntax is interchangeable, the compiler
     *       will then allow us to index the pointer to dynamically allocated
     *       memory as though it were a true (local) array: */
    arr[0] = first;
    arr[1] = second;

    return arr;
}
