#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>
#include <intrin.h>
#include <stdbool.h>

void cpuid(int code, uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d) {
    int regs[4];
    __cpuidex(regs, code, 0);
    *a = regs[0];
    *b = regs[1];
    *c = regs[2];
    *d = regs[3];
}

// Check if running in VirtualBox via CPUID
bool is_virtualbox_cpuid() {
    uint32_t eax, ebx, ecx, edx;
    char hypervisor_vendor[13];

    cpuid(0x40000000, &eax, &ebx, &ecx, &edx);

    // Combine EBX, ECX, and EDX into a string
    *((uint32_t*)(hypervisor_vendor))     = ebx;
    *((uint32_t*)(hypervisor_vendor + 4)) = ecx;
    *((uint32_t*)(hypervisor_vendor + 8)) = edx;
    hypervisor_vendor[12] = '\0';  // Null-terminate the string

    // Check if the hypervisor vendor is "VBoxVBoxVBox"
    if (strcmp(hypervisor_vendor, "VBoxVBoxVBox") == 0) {
        return true; 
    } else {
        return false; 
    }
}

bool file_exists(const char *filename) {
    DWORD file_attr = GetFileAttributes(filename);
    return file_attr != INVALID_FILE_ATTRIBUTES;
}

// Check if VirtualBox-related driver files exist
bool is_virtualbox_file() {
    // Check if VirtualBox driver files exist
    if (file_exists("C:\\Windows\\System32\\drivers\\VBoxMouse.sys") || 
        file_exists("C:\\Windows\\System32\\drivers\\VBoxGuest.sys")) {
        return true;
    } else {
        return false;
    }
}

int main() {
    // Detect if running inside VirtualBox using CPUID
    if (is_virtualbox_cpuid()) {
        printf("Detected VirtualBox via CPUID.\n");
    } else {
        printf("No VirtualBox detected via CPUID.\n");
    }

    // Detect if running inside VirtualBox by checking for driver files
    if (is_virtualbox_file()) {
        printf("Detected VirtualBox via driver files.\n");
    } else {
        printf("No VirtualBox detected via driver files.\n");
    }

    return 0;
}
