#include "../pmm.h"


static size_t get_bit(const uintptr_t PHYS) {
    return (PHYS % (PGE_SZ * 8 * 4) / 4096);
}

static size_t get_byte(const uintptr_t PHYS) {
    return PHYS / (PGE_SZ * 8 * 4);
}


void init_pmm(pmm_struct_t* pmm) {
    for (int i = 0; i < BMP_SZ; ++i) {
        pmm->bitmap[i] = 0;      // Null em.
    }
}


uintptr_t alloc_frame(pmm_struct_t* pmm) { 
    for (int byte = 0; byte < BMP_SZ; ++byte) {
        uint32_t dword = pmm->bitmap[byte];
        for (int bit = 0; bit < 32; ++bit, dword >>= 1) {
            if (!(dword & 0x1)) {       // If a bit is free.
                // Toggle the bit.
                pmm->bitmap[byte] ^= (0x1 << bit);
                // Return physical address.
                return 4096 * (8 * 4 * byte + bit);
            }
        }
    }
}


void free_frame(pmm_struct_t* pmm, const uintptr_t PHYS) {
    unsigned char bit = get_bit(PHYS);
    pmm->bitmap[get_byte(PHYS)] |= (0x0 << get_bit(PHYS));
}
