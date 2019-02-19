#include <stdio.h>

int main() {

    int sum = 0;
    int val;

    printf("Please input 10 integers: ");

    for (int i = 0; i < 10; i++) {
        scanf("%d", &val);
        sum += val;
    }

    printf("The sum is: %d\n", sum);
    printf("The average is: %f\n", ((float)sum / 10.0f));
    return 0;
}