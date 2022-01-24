global destub_kb_isr
global send_pic_end_int
global debug_putc
global _reset

destub_kb_isr:
    mov eax, 0x1
    mov ecx, [esp + 4]
    int 0x80
    ret

send_pic_end_int:
    mov al, 0x20
    out 0x20, al
    ret

debug_putc:
    mov eax, 0x4
    mov ecx, 'A'
    int 0x80
    ret

_reset:
    mov eax, 0x0
    int 0x80
