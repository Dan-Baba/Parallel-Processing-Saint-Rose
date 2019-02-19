#include <stdio.h>

int main(int arc, char* argv[]) {
    int x;
    float f;
    char line[80];

    printf("Hello there!\n\n");

    printf("Enter text: ");
    scanf("%s %d", line, &x);

    printf("You entered: %s\nInteger is: %d\n", line, x);
    return 0;
}