#define _KERNEL_START

char* vga_main = (char*)0xB8000;

#include "drivers/VGA.h"
#include "drivers/IO.h"
#include "drivers/floppy.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupt_handlers.h"
#include "interrupts/syscalls/syscalls.h"
#include "memory/GDT.h"


#define SW 80

static void unmask_kb_irq() {
    outportb(PIC1_DATA_PORT, 0xFD);
}


static void kb_isr_stub() {
    inportb(0x60);
    outportb(0x20, 0x20);
}

void _syscall_dispatcher();

int _ssmain();

int _start() {   
    _gdt_install();
    idt_install();
 
    set_idt_desc32(0x0, div_by_0_handler, TRAP_GATE_FLAGS);
    set_idt_desc32(0x21, kb_isr_stub, INT_GATE_FLAGS);
    set_idt_desc32(0x80, _syscall_dispatcher, INT_GATE_FLAGS);  
    unmask_kb_irq();
    __asm__ __volatile__("sti"); 

    vga_clear(&vga_main, 0x1, 0xE); 

    /*
    vga_puts("Drives Detected: ", &vga_main, 1);
    vga_puts("", &vga_main, 1);
    floppy_detect_drives();

    vga_main += 120;
    */

    vga_puts("Kernel Initialized.", &vga_main, 1);
    vga_puts("", &vga_main, 1);

    _ssmain();      // Run the kernel space startup shell.

    return 0;
}
