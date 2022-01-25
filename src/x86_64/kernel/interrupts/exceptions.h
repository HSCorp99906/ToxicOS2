#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "IDT.h"
#include "../drivers/VGA.h"


// 0xD
__attribute__((interrupt)) void gpf_handler(int_frame64_t* frame, uint64_t error_code) {
    outportb(0x3D4, 0x0A);
	outportb(0x3D5, 0x20);
    vga_clear(&vga_main, 0x4, 0xF);
    vga_puts("FATAL: General Protection Fault (", &vga_main, 0);
    vga_puts("(DESC: 0xD, EC: ", &vga_main, 0);
    vga_puts_dec(error_code, &vga_main, 0);
    vga_puts(")", &vga_main, 1);
    __asm__ __volatile__("cli; hlt");
}


#endif
