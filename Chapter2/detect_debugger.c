#include <stdio.h>
#include <windows.h>
#include <intrin.h>
#include <conio.h>

// Define necessary structures and function prototypes
typedef NTSTATUS (NTAPI *pNtQueryInformationProcess)(
    HANDLE ProcessHandle,
    UINT ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
);

typedef struct _PEB {
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    PVOID Ldr;
    PVOID ProcessParameters;
    BYTE Reserved4[104];
    PVOID Reserved5[52];
    PVOID PostProcessInitRoutine;
    BYTE Reserved6[128];
    PVOID Reserved7[1];
    ULONG SessionId;
} PEB, *PPEB;

typedef struct _PROCESS_BASIC_INFORMATION {
    PVOID Reserved1;
    PPEB PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    PVOID Reserved3;
} PROCESS_BASIC_INFORMATION;

#define ProcessBasicInformation 0

// Function to check if a debugger is present using the IsDebuggerPresent API
int checkDebuggerUsingIsDebuggerPresent() {
    return IsDebuggerPresent();
}

// Function to check if a debugger is present using the NtQueryInformationProcess API
int checkDebuggerUsingNtQueryInformationProcess() {
    BOOL isDebuggerPresent = FALSE;
    NTSTATUS status;
    HANDLE hProcess = GetCurrentProcess();
    PROCESS_BASIC_INFORMATION pbi;
    ULONG returnLength;

    status = NtQueryInformationProcess(hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), &returnLength);
    if (status == 0) {
        isDebuggerPresent = pbi.PebBaseAddress->BeingDebugged;
    }
    
    return isDebuggerPresent;
}

// Function to check if hardware breakpoints are set by inspecting debug registers
int checkDebuggerUsingDebugRegisters() {
    CONTEXT ctx = { 0 };
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if (GetThreadContext(GetCurrentThread(), &ctx)) {
        // Check if any debug registers are set
        if (ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3) {
            return 1;  // Debugger detected
        }
    }

    return 0;  // No debugger detected
}

int main() {
    if (checkDebuggerUsingIsDebuggerPresent()) {
        printf("Debugger detected using IsDebuggerPresent!\n");
    } else {
        printf("No debugger detected using IsDebuggerPresent.\n");
    }

    if (checkDebuggerUsingNtQueryInformationProcess()) {
        printf("Debugger detected using NtQueryInformationProcess!\n");
    } else {
        printf("No debugger detected using NtQueryInformationProcess.\n");
    }

    if (checkDebuggerUsingDebugRegisters()) {
        printf("Debugger detected using Debug Registers!\n");
    } else {
        printf("No debugger detected using Debug Registers.\n");
    }

    getch();
    return 0;
}
