#ifndef SYSCALLS_H
#define SYSCALLS_H

#define MAX_SYSCALLS 10

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
}

void syscall_update_menuentry() {
    register unsigned int num asm("ecx");

    switch (num) {
        case 1:
            drw_4_entry_menu("Credits", "UNUSED", "UNUSED", 
            "UNUSED", MENU_ENTRY_1);
            break;
        case 2:
            drw_4_entry_menu("Credits", "UNUSED", "UNUSED", 
            "UNUSED", MENU_ENTRY_2);
            break;
        case 3:
            drw_4_entry_menu("Credits", "UNUSED", "UNUSED", 
            "UNUSED", MENU_ENTRY_3);
            break;
        case 4:
            drw_4_entry_menu("Credits", "UNUSED", "UNUSED", 
            "UNUSED", MENU_ENTRY_4);
            break;
    }
}


void vga_clear_color() {
    const unsigned char RED = 0x01;
    const unsigned char GREEN = 0x2;
    const unsigned char PURPLE = 0x04;
    register unsigned char flags asm("ecx");

    if (flags & RED) {
        vga_clear(&vga_main, 0x04, 0xE);
    } else if (flags & GREEN) {
        vga_clear(&vga_main, 0x02, 0xE);
    } else if (flags & PURPLE) {
        vga_clear(&vga_main, 0x01 | 0x04, 0xE);
    }
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
    vga_clear_color,
    syscall_update_menuentry,
};

#endif
