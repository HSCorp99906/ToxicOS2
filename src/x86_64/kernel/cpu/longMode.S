global _lm_support_chk
global _lm_entry
global TSSDesc
extern _start

bits 32
_lm_entry:
    ; EDI => dest.
    mov edi, _l4_page_tbl
    push edi
    xor eax, eax
    mov ecx, 1024
    rep stosd       ; (*EDI = EAX++) REP = repeat

    mov edi, _l3_page_tbl
    mov ecx, 1024
    rep stosd

    pop edi
    mov cr3, edi                ; "Hey, CPU this is where the page table will be."
    mov eax, _l3_page_tbl
    add eax, 3
    mov [edi], eax
    
    xor eax, eax
    mov eax, 3 | (1 << 7) | (1 << 2)       ; Setting entry in l3 page table.
    mov [_l3_page_tbl], eax
 
    mov ebx, _l4_page_tbl
    mov ecx, _l3_page_tbl

    ; Enable PA.
    mov cr4, eax
    or eax, 1 << 5
    mov cr4, eax

    ; Set long mode bit.
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; "Yo CPU bro, we are using paging."
    mov eax, cr0
    or eax, (1 << 31) | 0x1
    mov cr0, eax

    lgdt [Pointer]
    jmp GDT64.Code:long_man

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

align 4096                  ; Each entry is 8 bytes and there is 
                            ; 512 entries. 8 * 5 = 4096
_l4_page_tbl: resb 4096
_l3_page_tbl: resb 4096


GDT64:                           ; Global Descriptor Table (64-bit).
    .Null: equ $ - GDT64         ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    .Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    .UserCode: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 11111010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .UserData: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 11110010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    TSSDesc:
        dq 0
        dq 0

    Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.


bits 64

global enter_usr_mode

long_man:   ; For long jump.
    mov ax, GDT64.Data
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    call _start
    jmp .post_exec

.post_exec:
    ; sti
    hlt
    jmp .post_exec
