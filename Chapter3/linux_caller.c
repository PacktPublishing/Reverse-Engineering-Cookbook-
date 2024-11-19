#include <stdio.h> 
extern void hello();  // Declaration of the function in the shared library 
int main() { 
    hello();  // Call the shared library function 
    return 0; 
} 
 
