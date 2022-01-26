#include "../TSS.h"


tss_entry_t kernel_tss;


void flush_tss();


void tss_init(uint32_t i, uint32_t kss, uint32_t kesp) {
    uint32_t base = (uint32_t)&kernel_tss;
    gdt_set_gate(i, base, base + sizeof(tss_entry_t), 0xE9, 0);
    _memset(&kernel_tss, 0, sizeof(tss_entry_t));
}
