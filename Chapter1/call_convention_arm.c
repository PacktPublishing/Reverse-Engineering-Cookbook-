#include <stdio.h> 

 int add_numbers(int a, int b, int c, int d, int e) { 
    return a + b + c + d + e; 
} 

int main() { 
    int result = 0; 

    // Call the function with five integers 
    result = add_numbers(1, 2, 3, 4, 5); 

    // Print the result 
    printf("The result is: %d\n", result); 
    return 0; 
} 

 