#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

// Method 1: Using the open() function
void open_with_standard_api() {
    const char *filename = "example.txt";
    int fd = open(filename, O_RDONLY);
    
    if (fd == -1) {
        perror("Failed to open file using open()");
    } else {
        printf("File opened successfully using open(), fd: %d\n", fd);
        close(fd);
    }
}

// Method 2: Using the syscall() function to directly invoke the openat system call
void open_with_syscall_api() {
    const char *filename = "example.txt";
    int fd;

    // Using syscall() to invoke the openat system call
    fd = syscall(SYS_openat, AT_FDCWD, filename, O_RDONLY);

    if (fd == -1) {
        perror("Failed to open file using syscall()");
    } else {
        printf("File opened successfully using syscall(), fd: %d\n", fd);
        close(fd);
    }
}

// Method 3: Using inline assembly to invoke the openat system call
void open_with_syscall_instruction() {
    const char *filename = "example.txt";
    int fd;

    __asm__ (
        "movq $0x101, %%rax\n"  // System call number (0x101 for openat)
        "movq $0xffffff9c, %%rdi\n"    // First argument: AT_FDCWD (current working directory)
        "movq %1, %%rsi\n"      // Second argument: filename
        "movq $0x0, %%rdx\n"    // Third argument: O_RDONLY
        "syscall\n"             // Make the system call
        "mov %%eax, %0\n"      // Store the return value in fd
        : "=r" (fd)
        : "r" (filename)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );

    if (fd == -1) {
        perror("Failed to open file using syscall instruction");
    } else {
        printf("File opened successfully using syscall instruction, fd: %d\n", fd);
        close(fd);
    }
}


int main() {
    // Call Method 1
    open_with_standard_api();

    // Call Method 2
    open_with_syscall_api();

    // Call Method 3
    open_with_syscall_instruction();

    return 0;
}

