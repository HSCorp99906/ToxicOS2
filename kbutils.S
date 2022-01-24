global _destub_kb_isr
global curs_move
global put_prompt
global send_pic_eoi
global get_key
global putch
global newline

_destub_kb_isr:
    mov eax, 0x1
    mov ecx, [esp + 4] 
    int 0x80
    ret

curs_move:
    mov eax, 0x2
    mov ecx, [esp + 4]  ; X.
    mov ebx, [esp + 8]  ; Y.
    int 0x80
    ret

put_prompt:
    mov eax, 0x3
    mov ecx, [esp + 4]
    mov ebx, 0
    int 0x80
    ret

putch:
    mov eax, 0x4
    mov ecx, [esp + 4]
    mov ebx, 0
    int 0x80
    ret

send_pic_eoi:
    mov al, 0x20
    out 0x20, al
    ret

newline:
    mov ecx, ""
    mov ebx, 1
    int 0x80
    ret
