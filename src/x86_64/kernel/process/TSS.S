global flush_tss

flush_tss:
    mov rax, 0x28
    ltr rax
    ret
