#include <stdio.h>
#include <pthread.h>
#define NUM_ROWS 9
#define NUM_COLS 9
#define NUM_CELLS NUM_ROWS*NUM_COLS

struct row_column {
    int row;
    int column;
};
int arrA[9][9] = {
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
    {7, 8, 8, 9, 11, 18, 90, 3, 4},
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
    {7, 8, 8, 9, 11, 18, 90, 3, 4},
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
    {7, 8, 8, 9, 11, 18, 90, 3, 4},
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
    {7, 8, 8, 9, 11, 18, 90, 3, 4},
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
};
int arrB[9][9] = {
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
    {7, 8, 8, 9, 11, 18, 90, 3, 4},
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
    {7, 8, 8, 9, 11, 18, 90, 3, 4},
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
    {7, 8, 8, 9, 11, 18, 90, 3, 4},
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
    {7, 8, 8, 9, 11, 18, 90, 3, 4},
    {5, 6, 8, 9, 10, 17, 16, 5, 8},
};
int arrC[9][9];

void printMatrix(int array[NUM_ROWS][NUM_COLS]);
void *DotProduct(void *arguments);
int main() {
    pthread_t threads[NUM_CELLS];
    struct row_column args[NUM_CELLS];
    // Get args in structs ready to pass to function.
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            int currIndex = (i*NUM_COLS) + j;
            args[currIndex].row = i;
            args[currIndex].column = j;
        }
    }

    // Make threads, passing args
    for (int i = 0; i < NUM_CELLS; i++) {
        pthread_create(&threads[i], NULL, DotProduct, (void *)&args[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_CELLS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result
    printMatrix(arrC);
    pthread_exit(NULL);
}

void printMatrix(int array[NUM_ROWS][NUM_COLS]) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

void *DotProduct(void *arguments) {
  struct row_column *args = (struct row_column *) arguments;
  int row = args->row;
  int col = args->column;
  printf("Thread calculating dot product for {%d, %d}\n", row, col);
  int sum = 0;
  for (int i = 0; i < NUM_COLS; i++) {
      sum += arrA[row][i] * arrB[i][col];
  }
  arrC[row][col] = sum;
  pthread_exit(NULL);
}