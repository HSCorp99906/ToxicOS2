#ifndef SYSCALLS_H
#define SYSCALLS_H

#define MAX_SYSCALLS 8

#include "../../drivers/IO.h"
#include "../../drivers/VGA.h"
#include "../IDT.h"
#include "../../util/types.h"


void syscall_restart() {
    outportb(0x64, 0xFE);
}


void syscall_curs_move() {
    register const uint16_t X asm("ecx");
    register const uint16_t Y asm("ebx"); 
    update_cursor(X, Y);
}


void syscall_change_kb_isr() {
    register void* isr asm("ecx");
    set_idt_desc32(0x21, isr, INT_GATE_FLAGS);
}


void syscall_puts() {
    register char* str asm("ecx");
    register unsigned char newlineBool asm("ebx");
    vga_puts(str, &vga_main, newlineBool);
}

void syscall_putc() {
    register char ch asm("ecx");
    register unsigned char newlineBool asm("ebx");
    char str[2] = "\0\0";
    str[0] = ch;
    vga_puts(str, &vga_main, newlineBool);
    vga_main -= 2;
}


void syscall_popc() {
    vga_main -= 2;
    *vga_main = ' ';
}


void reset_vga() {
    vga_clear(&vga_main, 0x1, 0xE);
    vga_puts("Kernel Initialized.", &vga_main, 1);
    vga_puts("", &vga_main, 1);
}


void display_disks() {
    floppy_detect_drives();
}


void* syscalls[MAX_SYSCALLS] = {
    syscall_restart,
    syscall_change_kb_isr,
    syscall_curs_move,
    syscall_puts,
    syscall_putc,
    syscall_popc,
    reset_vga,
    display_disks,
};

#endif
