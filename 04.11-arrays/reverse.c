#include <stdio.h>

void swap(int *, int *);
void reverse(int[], int);

int main(void) {
    int arr[] = {1, 2, 3, 4};

    /* NOTE: The length of an array is not an inherent attribute of the array
     *       itself; it must be passed separately if needed. */
    reverse(arr, 4);

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" |- %p: %d\n", (void *)&arr[1], arr[1]);
    printf(" |- %p: %d\n", (void *)&arr[2], arr[2]);
    printf(" +- %p: %d\n", (void *)&arr[3], arr[3]);

    return 0;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}

/* NOTE: In C, arguments are always pass-by-value, and the value of an array is
 *       the address of its first element, so an array "decays" into a pointer
 *       when it is passed as an argument. Modifications to elements also affect
 *       the caller's array, and it is *never* safe to return a local array. */
void reverse(int arr[], int len) {
    int i;

    for (i = 0; i < len / 2; i++) {
        swap(&arr[i], &arr[len - 1 - i]);
    }
}
