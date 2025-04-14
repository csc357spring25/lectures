#include <stdio.h>

/* NOTE: The value of an array is the address of its first element, so the
 *       value of an array of integer pointers is the address of an integer
 *       pointer -- an integer double pointer. The compiler allows us to use
 *       pointer and array syntax interchangeably. */
void foo(int **mat) {
    mat[0][1] = 5;
}

/* NOTE: In order to make the indexing math work, the compiler must know the
 *       length of each "inner" array. This, however, only works as long as we
 *       only ever call this function with n x 2 arrays. */
void bar(int mat[][2]) {
    mat[0][1] = 5;
}

/* NOTE: In order to take any n x m array as input, we could instead take what
 *       is actually an array of arrays of integers as an ordinary integer
 *       pointer. The compiler won't know how to index that pointer, but we the
 *       programmers do, and we can do the math for the compiler. */
void bay(int *mat, int m) {
    *(mat + (0 * m) + 1) = 6;
}

int main(void) {
    /* NOTE: To declare an array of integer pointers: */
    int r0[] = {1, 2}, r1[] = {3, 4};
    int *mat1[2];

    /* NOTE: To declare an equivalent multidimensional array: */
    int mat2[][2] = {{1, 2}, {3, 4}};

    mat1[0] = r0;
    mat1[1] = r1;
    foo(mat1);

    printf("mat1: %p\n", (void *)mat1);
    printf(" |- %p: %p\n", (void *)&mat1[0], (void *)mat1[0]);
    printf(" |----- %p: %d\n", (void *)&mat1[0][0], mat1[0][0]);
    printf(" |----- %p: %d\n", (void *)&mat1[0][1], mat1[0][1]);
    printf(" |- %p: %p\n", (void *)&mat1[1], (void *)mat1[1]);
    printf(" |----- %p: %d\n", (void *)&mat1[1][0], mat1[1][0]);
    printf(" +----- %p: %d\n", (void *)&mat1[1][1], mat1[1][1]);

    bar(mat2);
    bay((int *)mat2, 2);

    printf("mat2: %p\n", (void *)mat2);
    printf(" |- %p: %p\n", (void *)&mat2[0], (void *)mat2[0]);
    printf(" |----- %p: %d\n", (void *)&mat2[0][0], mat2[0][0]);
    printf(" |----- %p: %d\n", (void *)&mat2[0][1], mat2[0][1]);
    printf(" |- %p: %p\n", (void *)&mat2[1], (void *)mat2[1]);
    printf(" |----- %p: %d\n", (void *)&mat2[1][0], mat2[1][0]);
    printf(" +----- %p: %d\n", (void *)&mat2[1][1], mat2[1][1]);

    return 0;
}
