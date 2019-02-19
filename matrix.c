#include <stdio.h>

void printMatrix(int array[2][2]);
int main() {
    int arrA[2][2] = {
        {1, 2},
        {3, 4}
    };
    int arrB[2][2] = {
        {5, 6},
        {7, 8}
    };

    printMatrix(arrA);
    return 0;
}

void matrixMultiply(int matrixA[2][2], int matrixB[2][2]) {

}

void printMatrix(int array[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}