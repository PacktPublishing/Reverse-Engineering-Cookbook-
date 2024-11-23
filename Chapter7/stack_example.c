#include <stdio.h>

void target_function(int a, int b, int c, int d, int e, int f, int g, int h) {
    char buffer[16];
    int sum = a + b + c + d + e + f + g + h;  
    printf("Address of buffer: %p\n", buffer);
    printf("Sum of all parameters: %d\n", sum);
}

int main() {
    target_function(1, 2, 3, 4, 5, 6, 7, 8);
    return 0;
}
