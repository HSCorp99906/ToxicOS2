global _syscall_dispatcher
extern syscalls

%define MAX_SYSCALLS 8

_syscall_dispatcher:
    cmp eax, MAX_SYSCALLS - 1
    jg .ignore

    cmp eax, 0
    jl .ignore

    pusha
    call [syscalls + eax * 4]  ; Each entry is 4 bytes.
    popa

    iretd

.ignore:
    iretd
