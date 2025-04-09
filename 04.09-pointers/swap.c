#include <stdio.h>

/* NOTE: To declare a function that takes two int pointers, returns nothing: */
void swap(int *, int *);

int main(void) {
    int z = 1, w = 2;

    /* NOTE: To call a function that takes two int pointers: */
    swap(&z, &w);

    printf("z (%p): %d\n", (void *)&z, z);
    printf("w (%p): %d\n", (void *)&w, w);

    return 0;
}

/* NOTE: In C, arguments are always pass-by-value, but the value of a pointer
 *       is a reference. Passing a pointer emulates pass-by-reference behavior,
 *       essentially telling a function *where* the arguments can be found
 *       rather than than *what* the arguments are. */
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}
