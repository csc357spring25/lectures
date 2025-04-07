/* NOTE: To copy-paste the contents of stdio.h from the standard library: */
#include <stdio.h>
/* NOTE: To copy-paste the contents of add.h from the current directory: */
#include "add.h"

int main(void) {
    /* NOTE: To call a function that takes two ints and returns an int: */
    printf("add(1, 2): %d\n", add(1, 2));   

    /* NOTE: To use a macro that does the same thing: */
    printf("ADD(1, 2): %d\n", ADD(1, 2));   

    return 0;
}
