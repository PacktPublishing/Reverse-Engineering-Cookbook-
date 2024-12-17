#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;

    printf("Values on the stack:\n");
    printf("1st argument: %1$d\n", a, b, c);
    printf("2nd argument: %2$d\n", a, b, c);
    printf("3rd argument: %3$d\n", a, b, c);

    return 0;
}
