#include "../vmm.h"


static void _init_id() {
    
}


void set_entry(uint64_t* page, uint64_t addr, uint64_t flags) {
    uint64_t entry = (uint64_t)addr;
    entry |= PAGE_PRESENT | flags;
    *page = entry;
}


static unsigned char _is_present(uint64_t* page) {
    return (page & 0x1) == 0x1;
}


void vmm_init() {
    
}
