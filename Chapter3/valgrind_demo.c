#include <stdio.h>
#include <stdlib.h>

void memory_leak() {
    int *array = (int *)malloc(10 * sizeof(int));
    // free(array);
}

void uninitialized_memory_access() {
    int *uninitialized_array = (int *)malloc(5 * sizeof(int));

    printf("Uninitialized value: %d\n", uninitialized_array[2]);

    free(uninitialized_array);
}

int main() {
    memory_leak();
    uninitialized_memory_access();
    return 0;
}
