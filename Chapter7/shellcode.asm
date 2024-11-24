BITS 64

section .text
global _start

_start:
    ; Get PEB address (In Windows x64, the PEB address is stored at offset 0x60 in the GS register)
    mov     rbx, gs:[0x60]               ; rbx = PEB base address

    ; Traverse the PEB loaded module list to find the base address of kernel32.dll
    mov     rbx, [rbx + 0x18]            ; PEB_LDR_DATA address
    mov     rbx, [rbx + 0x10]            ; InMemoryOrderModuleList (points to the first module)

find_kernel32:
    mov     rbx, [rbx]                   ; Next module (doubly linked list)
    mov     rsi, [rbx + 0x30]            ; Get DLL base address
    mov     rdi, [rbx + 0x60]            ; Get module name address
    mov     rax, 0x6c6c656b              ; Little-endian representation of "kell" (first part of "kernel32.dll")
    cmp     qword [rdi], rax             ; Compare the first 4 bytes
    jne     find_kernel32                ; If not, continue searching
    cmp     word [rdi + 4], 0x3233       ; Compare "32" (remaining part of "kernel32")
    jne     find_kernel32                ; If not, continue searching

    ; Find the address of GetProcAddress
    ; Use the base address of kernel32.dll
    mov     rdx, rsi                     ; rdx = kernel32.dll base address
    mov     rax, [rdx + 0x3C]            ; Get PE header offset
    add     rax, rdx                     ; rax = PE header address
    mov     eax, [rax + 0x88]            ; Get export table offset (Optional Header -> DataDirectory -> Export Table)
    test    rax, rax                     ; Check if export table exists
    jz      exit                         ; If not, exit
    add     rax, rdx                     ; rax = Export Table RVA
    mov     rbx, [rax + 0x18]            ; Get function name address array offset
    add     rbx, rdx                     ; rbx = Function name address array base
    mov     rcx, [rax + 0x20]            ; Get function name ordinal array offset
    add     rcx, rdx                     ; rcx = Function name ordinal array base
    mov     r8, [rax + 0x1C]             ; Get function address array offset
    add     r8, rdx                      ; r8 = Function address array base

find_getprocaddress:

    mov     rdi, [rbx]                   ; Get function name address
    add     rdi, rdx                     ; rdi = Function name absolute address
    mov     rax, 0x50726f63              ; Little-endian representation of "Proc"
    cmp     dword [rdi], eax             ; Compare "Proc"
    jne     next_function                ; If not, continue searching
    mov     rax, 0x74736547              ; Little-endian representation of "Get"
    cmp     dword [rdi + 4], eax         ; Compare "Get"
    jne     next_function                ; If not, continue searching

    jmp     getprocaddress_found
next_function:
    add     rbx, 8                       ; Move to the next function name address
    add     rcx, 2                       ; Move to the next ordinal
    add     r8, 4                        ; Move to the next function address
    jmp     find_getprocaddress          ; Continue searching          ; If not, continue searching
getprocaddress_found:
    ; Get function address
    movzx   eax, word [rcx]              ; Get function ordinal
    shl     rax, 2                       ; Ordinal * 4
    add     r8, rax                      ; Get address in function address array
    mov     eax, [r8]                    ; Get function RVA
    add     rax, rdx                     ; Calculate absolute address of GetProcAddress
    mov     rcx, rax                     ; Store GetProcAddress address in rcx

    ; Use GetProcAddress to find the address of MessageBoxA
    ; Set up parameters and call GetProcAddress
    mov     r9, rsi                      ; r9 = kernel32.dll base address
    call    get_message_box_a            ; Get address of "MessageBoxA" string
    db      "MessageBoxA", 0
get_message_box_a:
    pop     r8                           ; r8 = "MessageBoxA" string address
    sub     rsp, 32                      ; Allocate stack space for calling convention
    call    rcx                          ; Call GetProcAddress(kernel32.dll, "MessageBoxA")
    add     rsp, 32                      ; Restore stack space
    mov     rdx, rax                     ; rdx = MessageBoxA address

    ; Set up MessageBoxA parameters and call it
    xor     rcx, rcx                     ; hWnd = NULL
    call    get_title_str                ; Get address of "Title" string
    db      "Title", 0
get_title_str:
    pop     r8                           ; r8 = "Title" string address
    call    get_text_str                 ; Get address of "Hello, World!" string
    db      "Hello, World!", 0
get_text_str:
    pop     r9                           ; r9 = "Hello, World!" string address
    mov     r10, 0                       ; uType = MB_OK
    sub     rsp, 32                      ; Allocate stack space for calling convention
    call    rdx                          ; Call MessageBoxA(NULL, "Hello, World!", "Title", MB_OK)
    add     rsp, 32                      ; Restore stack space

exit:
    ; Exit program
    mov     rax, 60                      ; System call: exit
    xor     rdi, rdi                     ; Return code 0
    syscall
