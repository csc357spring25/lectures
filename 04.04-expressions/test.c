#include <stdio.h>

int main(void) {

    /* NOTE: This is allowed, but because x is declared as short, it typically
     *       occupies only 16 bits in memory, so this overflows: */
    short int x = 16384;
    printf("x: %d\n", x);
    x *= 2;
    printf("x: %d\n", x);

    /* NOTE: This is not allowed; since x is declared as an int, it cannot be
     *       changed to a string:
     * x = "0"; */
    x = 0;
    printf("x: %d\n", x);

    /* NOTE: This is syntactically valid, but it evaluates to (-1 < x) < 1,
     *       which is (-1 < 0) < 1, which 1 < 1, which is 0: */
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* NOTE: This will not compile; local variables must be declared as soon as
     *       they come into scope:
     * int y = 1; */

    /* NOTE: This introduces a new scope: */
    {
        int y = 1;
        printf("y (inside): %d\n", y);

        {
            /* NOTE: This "shadows" the existing x: */
            int x = 2;
            printf("x (ininside): %d\n", x);
        }

        /* NOTE: This uses the existing x from the enclosing scope: */
        x = 3;
        printf("x (inside): %d\n", x);
    }

    /* NOTE: This will not compile; y is only in scope within the block:
     * printf("y (outside): %d\n", y); */
    printf("x (outside): %d\n", x);

    return 0;
}
