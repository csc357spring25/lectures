#include <stdio.h>
#include "add.h"
#include "max.h"

int reduce(int[], int, int (*)(int, int));

int main(void) {
    int arr[] = {1, 2, 3, 4};

    /* NOTE: To call a function and pass it a pointer to another function; this
     *       allows us to define functions that perform arbitrary operations
     *       using other functions that they are passed: */
    printf("reduce(arr, 4, add): %d\n", reduce(arr, 4, add));
    printf("reduce(arr, 4, max): %d\n", reduce(arr, 4, max));

    return 0;
}

/* NOTE: To define a function that takes as argument a pointer to another
 *       function that takes as argument two ints and returns an int: */
int reduce(int arr[], int n, int (*fn)(int, int)) {
    int val = arr[0], i;

    for (i = 1; i < n; i++) {
        /* NOTE: To dereference a function pointer -- to use the value to which
         *       it points -- is to call that function. */
        val = (*fn)(val, arr[i]);
    }

    return val;
}
