bits 32

MAGIC_NUMBER equ 0x1BADB002
ALIGN_MODULES equ 0x00000001
CHECKSUM equ -(MAGIC_NUMBER + ALIGN_MODULES)

section .text
    align 4
    dd MAGIC_NUMBER
    dd ALIGN_MODULES
    dd CHECKSUM
        
global start
extern _start
extern _lm_entry
start:
    cli
    jmp _lm_entry 
