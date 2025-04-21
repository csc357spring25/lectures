#include <stdio.h>
#include "pair.h"

/* NOTE: The value of a structure is the whole structure; a structure as an
 *       argument is a copy of that structure, and we must return it if we want
 *       access to it outside of a function... */
Pair foo(Pair pair) {
    pair.first = 3;

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- first  (%p): %d\n", (void *)&pair.first, pair.first);
    printf(" +- second (%p): %d\n", (void *)&pair.second, pair.second);

    return pair;
}

/* NOTE: ...if we the programmers determine that we would rather pass a
 *       structure by reference, whether for convenience or for efficiency,
 *       we can always pass a pointer instead. */
void bar(Pair *pair) {
    pair->second = 4;

    /* NOTE: The dot operator has precedence over the dereference operator;
     *       without the parentheses, we would be dereferencing a pointer *in*
     *       a structure rather than a pointer *to* a structure:
     * (*pair).second = 4; */

    printf("pair (%p): %p\n", (void *)&pair, (void *)pair);
    printf(" |- first  (%p): %d\n", (void *)&(*pair).first, (*pair).first);
    printf(" +- second (%p): %d\n", (void *)&(*pair).second, (*pair).second);
}

int main(void) {
    /* NOTE: To instantiate a value of type "Pair": */
    Pair pair = {1, 2};

    /* NOTE: To pass a value of type "Pair": */
    pair = foo(pair);

    /* NOTE: To pass a pointer to a value of type "Pair": */
    bar(&pair);

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- first  (%p): %d\n", (void *)&pair.first, pair.first);
    printf(" +- second (%p): %d\n", (void *)&pair.second, pair.second);

    return 0;
}
