global _syscall_dispatcher
extern syscalls

%define MAX_SYSCALLS 11

_syscall_dispatcher:
    cmp eax, MAX_SYSCALLS - 1
    jg .ignore

    cmp eax, 0
    jl .ignore

    call [syscalls + eax * 4]  ; Each entry is 4 bytes.

    iretd

.ignore:
    iretd
