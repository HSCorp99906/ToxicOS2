global asm_move_curs

asm_move_curs:
    mov ecx, [esp + 4]
    mov ebx, 0x0
    mov eax, 0x1
    int 0x80
    ret
