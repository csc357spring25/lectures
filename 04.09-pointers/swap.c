#include <stdio.h>

void swap(int, int);

int main(void) {
    int z = 1, w = 2;

    swap(z, w);

    printf("z (%p): %d\n", (void *)&z, z);
    printf("w (%p): %d\n", (void *)&w, w);

    return 0;
}

void swap(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
}
