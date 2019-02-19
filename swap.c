#include <stdio.h>

void swap(int* x, int* y);

int main(int arc, char* argv[]) {
    int a = 5;
    int b = 7;

    printf("a: %d b: %d\n", a, b);
    swap(&a,&b);
    printf("a: %d b: %d\n", a, b);
    return 0;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}