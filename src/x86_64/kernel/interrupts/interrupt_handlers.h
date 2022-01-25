#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

#include "IDT.h"
#include "../drivers/IO.h"

__attribute__((interrupt)) void div_by_0_handler(int_frame64_t* frame) {
    char* vga = (char*)0xB8000;
    vga_clear(&vga, 0x04, 0x07 + 0x08);
    vga_puts("FATAL: Division by zero exception caught (System Halted).\0", &vga, 0);
    __asm__ __volatile__("cli; hlt");
}

__attribute__((interrupt)) void stub_isr(int_frame64_t* frame) {}

__attribute__((interrupt)) void _reboot(int_frame64_t* frame) {
    outportb(0x64, 0xFE);
}


#endif
