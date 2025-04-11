#include <stddef.h>

int main(void) {
    int *ptr = NULL;

    /* NOTE: This is guaranteed to cause an error, likely a segfault, since a
     *       null pointer is never a valid address for data. */
    *ptr = 2;

    return 0;
}
