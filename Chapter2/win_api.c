#include <windows.h>
#include <winternl.h>
#include <stdio.h>

// Link with ntdll.lib for Native API functions
#pragma comment(lib, "ntdll.lib")

// Native API function prototypes
typedef NTSTATUS (NTAPI *NtQuerySystemInformation_t)(
    SYSTEM_INFORMATION_CLASS SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
);

// Syscall number for NtQuerySystemInformation
#define SYSCALL_NUMBER_NtQuerySystemInformation 0x0000000C
#define SYS_NtQuerySystemInformation 0x0000000C
#define STATUS_INFO_LENGTH_MISMATCH  ((NTSTATUS)0xC0000004L)

// Syscall function prototype
typedef NTSTATUS (NTAPI *Syscall_t)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
);

int main() {
    // Win32 API: Show a MessageBox
    MessageBoxA(NULL, "This is a Win32 API MessageBox!", "Win32 API", MB_OK);

    // Native API: Query system information
    NtQuerySystemInformation_t NtQuerySystemInformation;
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    NtQuerySystemInformation = (NtQuerySystemInformation_t)GetProcAddress(ntdll, "NtQuerySystemInformation");

    if (NtQuerySystemInformation) {
        ULONG len = 0;
        NTSTATUS status = NtQuerySystemInformation(SystemBasicInformation, NULL, 0, &len);
        if (status == STATUS_INFO_LENGTH_MISMATCH) {
            printf("Native API call successful. Required buffer size: %lu bytes\n", len);
        } else {
            printf("Native API call failed with status: 0x%X\n", status);
        }
    } else {
        printf("Failed to load NtQuerySystemInformation from ntdll.dll\n");
    }

    // Syscall: Demonstrate calling a syscall
    // This part is more complex and typically requires platform-specific tools or methods
    // For illustration, we're not implementing a real syscall here

// Syscall: Using inline assembly to invoke syscall directly
    SYSTEM_BASIC_INFORMATION sysInfo;
    ULONG len;
    NTSTATUS status;

    /*
    __asm {
        mov rax, SYS_NtQuerySystemInformation  // syscall number
        mov rdi, 0                           // SystemBasicInformation
        mov rsi, offset sysInfo              // Output buffer
        mov rdx, sizeof(sysInfo)             // Buffer size
        mov rcx, offset len                  // Length of output buffer
        syscall                              // Make the syscall
        mov status, rax                      // Get return status
    }
    */
    if (status == 0) { // STATUS_SUCCESS
        printf("Syscall succeeded. Number of processors: %u\n", sysInfo.NumberOfProcessors);
    } else {
        printf("Syscall failed with status: 0x%X\n", status);
    }

    return 0;
}
