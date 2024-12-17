#include <stdio.h>
#include <string.h>

void vulnerable_function() {
    char buffer[100];
    puts("Enter your input:");
    memset(buffer, 0, sizeof(buffer));
    fgets(&buffer, sizeof(buffer), stdin);
    printf(buffer);
    printf("\n");
}

int main(int argc, char *argv[]) {
    while(1) {
        vulnerable_function();
    }
    return 0;
}
