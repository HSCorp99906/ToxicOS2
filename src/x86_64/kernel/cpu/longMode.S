global _lm_support_chk
_lm_support_chk:
    ; Copy flags into EAX.
    pushfd
    pop eax

    ; Copy to ecx.
    mov ecx, eax
    xor eax, 1 << 21

    ; Copy EAX to flags.
    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    xor eax, ecx
    jz .FALSE
 
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .FALSE

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .FALSE

    mov eax, 1
    ret

.FALSE:
    mov eax, 0
    ret
