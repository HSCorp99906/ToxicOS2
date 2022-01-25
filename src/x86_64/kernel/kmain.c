#define _KERNEL_START
#define NULL 0

char* vga_main = (char*)0xB8000;

#include "drivers/VGA.h"
#include "drivers/IO.h"
#include "drivers/floppy.h"
#include "drivers/PCI_IDE_ATA.h"
#include "drivers/graphics.h"
#include "drivers/mouse.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupt_handlers.h"
#include "interrupts/syscalls/syscalls.h"
#include "interrupts/exceptions.h"

#define SW 80

static void unmask_kb_irq() {
    outportb(PIC1_DATA_PORT, 0xFD);
}


__attribute__((interrupt)) static void kb_isr_stub(int_frame64_t*) {
    inportb(0x60);
    outportb(0x20, 0x20);
}


static void panic(const char* reason) {
     outportb(0x3D4, 0x0A);
	 outportb(0x3D5, 0x20);
     vga_clear(&vga_main, 0x4, 0xF);
     vga_puts("**** KERNEL PANIC ****", &vga_main, 1);
     vga_puts("", &vga_main, 1);
     vga_puts(reason, &vga_main, 1);
     __asm__ __volatile__("cli; hlt");
}


unsigned char _lm_support_chk();
void _syscall_dispatcher();
int _ssmain();
void jump_usermode();

int _start() {
    vga_clear(&vga_main, 0x1, 0xE);
    drw_4_entry_menu("Credits", "UNUSED", "UNUSED", 
            "UNUSED", MENU_ENTRY_1);
    
    idt_install();  
    set_idt_desc64(0x0, div_by_0_handler);
    set_idt_desc64(0xD, gpf_handler);
    set_idt_desc64(0x21, div_by_0_handler);
    set_idt_desc64(0x80, _syscall_dispatcher);
    unmask_kb_irq();


    update_cursor(20, 0);       // += 15 to advance to next entry.

    /*
    vga_puts("Drives Detected: ", &vga_main, 1);
    vga_puts("", &vga_main, 1);
    floppy_detect_drives();

    vga_main += 120;
    */

    // _ssmain();      // Run the kernel space startup shell.

    return 0;
}
