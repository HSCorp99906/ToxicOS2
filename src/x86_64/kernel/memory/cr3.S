global _write_cr3
global _read_cr3

_write_cr3:
    mov cr3, rdi
    ret

_read_cr3:
    mov rax, cr3
    ret
