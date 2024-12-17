#include <stdio.h>

int main() {
    int count1 = 0; // Variable to store the character count for the first %n
    int count2 = 0; // Variable to store the character count for the second %n

    printf("This is a test.%n, Adding more text.%n\n", &count1, &count2);

    printf("Cumulative character counts at respective positions: %d, %d\n", count1, count2);

    return 0;
}
