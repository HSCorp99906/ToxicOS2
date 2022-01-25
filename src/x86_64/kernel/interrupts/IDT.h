#ifndef idt64_H
#define idt64_H

#define idt64_SIZE 256

#define TRAP_GATE_FLAGS 0x8F
#define INT_GATE_FLAGS 0x8E
#define INT_GATE_USER_FLAGS 0xEE

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21

#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1


#include "../drivers/VGA.h"
#include "../drivers/IO.h"
#include "../util/types.h"

/* 
 * Each entry describes where ISR
 * is located in memory to service
 * the interrupt.
 */

typedef struct {
    uint16_t isr_addr_low;
    uint16_t kernel_cs;         // Code segment where the ISR is.
    uint8_t ist : 3;            // Interrupt stack table. TODO: Research.
    uint8_t reserved : 5;       // Reserved by intel for some reason.
    uint8_t attr : 4;
    uint8_t zero1 : 1;
    uint8_t dpl : 2;            // Descriptor privellege level.
    uint8_t p : 1;              // Present.
    uint16_t isr_addr_middle;   // 64 bits means more bits dummy.
    uint32_t isr_addr_high;
    uint32_t reserved2;         // This was it.
} __attribute__((packed)) idt_entry64_t;


/*
 *  idt64R describes where in memory
 *  the idt64 is.
 */

typedef struct {
    uint16_t limit;         // Max address of idt64.
    uint64_t base;          // Lowest address of idt64.
} __attribute__((packed)) idtr64_t;

idt_entry64_t idt64[idt64_SIZE];     // Actual IDT.
idtr64_t idtr64;

typedef struct {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((packed)) int_frame64_t;


/*
 * Interrupt attribute will
 * return with IRET, not RET.
 */


__attribute__((interrupt)) void default_int_handler(int_frame64_t* frame) {
    __asm__ __volatile__("cli; hlt");
}


void set_idt_desc64(uint8_t entry, void* isr) {
    uint64_t addr = (uint64_t)isr;

    idt64[entry].isr_addr_low = addr & 0xFFFF;
    idt64[entry].isr_addr_middle = (addr & 0xFFFF0000) >> 16;
    idt64[entry].isr_addr_high = (addr & 0xFFFFFFFF00000000) >> 32;

    idt64[entry].dpl = 0;
    idt64[entry].p = 1;
    idt64[entry].attr = 0xF;
    idt64[entry].kernel_cs = 0x08;
    idt64[entry].reserved = 0x0;
    idt64[entry].reserved2 = 0x0;
}


void _lidt(idtr64_t*);

void idt_install() {
    idtr64.limit = (uint16_t)(sizeof(idt_entry64_t) * 256);
    idtr64.base = (uint64_t)&idt64; 

    unsigned char a1,a2;
    a1 = inportb(0x21);             // Get master mask.
    a2 = inportb(0xA1);             // Get slave mask.

    outportb(0x20,0x10 | 0x01);     // Tell the PIC we want to initialize it
    outportb(0xA0,0x10 | 0x01);
    outportb(0x21, 0x20);         // Master PIC offset.
    outportb(0xA1, 0x28);         // Slave PIC offset.

    outportb(0x21,0x04);            // Tell master PIC there is a slave PIC at IRQ2.
    outportb(0xA1,0x02);            // Tell slave PIC its cascade identity.

    outportb(0x21,0x01);            // Put the master PIC into 8086 mode.
    outportb(0xA1,0x01);            // Put the slave PIC into 8086 mode.

    outportb(0x21,a1);              // Restore the masks.
    outportb(0xA1,a2);

    for (int i = 0; i < 256; ++i) {
        idt64[i].isr_addr_low = 0x0;
        idt64[i].isr_addr_middle = 0x0;
        idt64[i].isr_addr_high = 0x0;

        idt64[i].dpl = 0x0;
        idt64[i].p = 0x0;
        idt64[i].attr = 0x0;
        idt64[i].kernel_cs = 0x0;
    }

    _lidt(&idtr64);

}  
#endif
