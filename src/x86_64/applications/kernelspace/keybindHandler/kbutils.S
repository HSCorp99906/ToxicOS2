global destub_kb_isr
global send_pic_end_int
global debug_putc
global _reset
global color_change
global kprint
global update_entry
global _curs_move
global _clear_screen

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

kputs:
    mov eax, 0x3
    mov ecx, [esp + 4]
    mov ebx, 0
    int 0x80
    ret

color_change:
    mov eax, 0x8
    mov ecx, [esp + 4]
    int 0x80
    ret

kprint:
    mov eax, 0x3
    mov ecx, [esp + 4]
    int 0x80
    ret

update_entry:
    mov eax, 0x9
    mov ecx, [esp + 4]
    int 0x80
    ret

_curs_move:
    mov eax, 0x2
    mov ecx, [esp + 4]
    mov ebx, [esp + 8]
    int 0x80
    ret

_clear_screen:
    mov eax, 0xA
    int 0x80
    ret
