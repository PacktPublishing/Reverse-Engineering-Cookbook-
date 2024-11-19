#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle = dlopen("./linux_lib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    void (*hello)() = dlsym(handle, "hello");
    if (!hello) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    hello();  // Call the function from the shared library

    dlclose(handle);
    return 0;
}

