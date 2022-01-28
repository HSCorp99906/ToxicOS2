#include "../vmm.h"



void set_entry(uint64_t* page, uint64_t addr, uint64_t flags) {
    uint64_t entry = (uint64_t)addr;
    entry |= PAGE_PRESENT | flags | PAGE_USER;
    *page = entry;
}


void _write_cr3(void* addr);
uint64_t _read_cr3();
__attribute__((aligned(4096))) static uint64_t id_page[512];

static void _init_id() {
    _memset((unsigned char*)id_page, 4096, 0);
    uint64_t* id = (uint64_t*)id_page;
    uint32_t ram = RAM;

    ram /= (1 << 30);
    ++ram;

    while (ram--) {
        set_entry(&id[ram], ram * _1GB, PAGE_RW | PAGE_SIZE);
    }
}

static void _map_id(uint64_t* l4) {
    static uint64_t idx = ID_OFFSET >> 39;
    set_entry(&l4[idx], (uint64_t)id_page, PAGE_RW);
}


static unsigned char _is_present(uint64_t page) {
    return (page & 0x1) == 0x1;
}


uint64_t* alloc_page_table() {
    uint64_t new_frame = (uint64_t)alloc_frame();
    new_frame = HIGH(new_frame);
    return (uint64_t*)new_frame;
}


uint64_t create_address_space() {
    uint64_t* l4 = alloc_page_table();
    uint64_t* l3 = alloc_page_table();
    uint64_t* l2 = alloc_page_table();
    
    for (int i = 0; i < 4; ++i) {
        set_entry(&l2[i], ((uint64_t)_1MB * 2) * i, PAGE_RW | PAGE_SIZE); 
    }

    _map_id((uint64_t*)l4);

    set_entry(&l4[0], LOW((uint64_t)l3), PAGE_RW);
    set_entry(&l3[0], LOW((uint64_t)l2), PAGE_RW);
    return LOW((uint64_t)l4);
}

void vmm_init() {
    _init_id();
    _map_id((uint64_t*)_read_cr3());
    // void* ptr = (void*)create_address_space();
    // _write_cr3(ptr);
}
