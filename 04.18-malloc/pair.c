#include <stdio.h>
#include <stdlib.h>

int *pair(int, int);

int main(void) {
    int *arr;

    /* NOTE: If this pointer to dynamically allocated memory is never freed,
     *       this would be a memory leak of 8 bytes. */
    arr = pair(1, 2);

    /* NOTE: This is invalid; it makes no sense to deallocate memory on the
     *       runtime stack:
     * free(&arr); */

    /* NOTE: This is also invalid; only entire dynamically allocated blocks
     *       can be deallocated, not portions within blocks:
     * free(arr + 1); */

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    /* NOTE: At this point, we no longer intend to use the memory, so we should
     *       deallocate it: */
    free(arr);

    /* NOTE: This is also invalid; it makes no sense to deallocate the same
     *       memory twice:
     * free(arr); */

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
