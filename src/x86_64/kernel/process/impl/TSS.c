#include "../TSS.h"


tss_entry_t kernel_tss;


void switch_to_user_mode() {
   // Set up a stack structure for switching to user mode.
   asm volatile("  \
     cli; \
     mov $0x23, %ax; \
     mov %ax, %ds; \
     mov %ax, %es; \
     mov %ax, %fs; \
     mov %ax, %gs; \
                   \
     mov %esp, %eax; \
     pushl $0x23; \
     pushl %eax; \
     pushf; \
     pushl $0x1B; \
     push $1f; \
     iret; \
   1: \
     ");
}


void flush_tss();

static void _tssDesc(tss_entry_t* entry) {
    uint64_t addr = (uint64_t)entry;
    TSSDesc.baseAddrLow = addr & 0xFFFF;        // Sets higher part of addr to zeros.
    TSSDesc.baseAddrMiddle = (addr & 0xFF0000) >> 16;
    TSSDesc.baseAddrOtherMiddle = (addr & 0xFF000000) >> 24;
    TSSDesc.baseAddrUpper = (addr & 0xFFFFFFFF00000000) >> 32;
    TSSDesc.p = 1;
    TSSDesc.type = 0xB;
}


void tss_init(uint32_t i, uint32_t kss, uint32_t kesp) {
    uint32_t base = (uint32_t)&kernel_tss;
    gdt_set_gate(i, base, base + sizeof(tss_entry_t), 0xE9, 0);
    _memset(&kernel_tss, 0, sizeof(tss_entry_t));
}
