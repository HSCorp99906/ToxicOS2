#include "../pmm.h"

static size_t mem_used = 0;

size_t frame_bytes_allocated() {
    return mem_used;
}


static size_t _get_bit(const uintptr_t PHYS) {
    return (PHYS % (PGE_SZ * 8 * 4) / 4096);
}


static size_t _get_byte(const uintptr_t PHYS) {
    return PHYS / (PGE_SZ * 8 * 4);
}


void init_pmm(pmm_struct_t* pmm) {
    for (int i = 0; i < BMP_SZ; ++i) {
        pmm->bitmap[i] = 0;      // Null em.
    }

    for (int i = 0; i < 32; ++i) {
        pmm->bitmap[i] = ~0;
    }
}

// Allocates 4 bytes.
/*
 * FIXME: Idk if this is a problem, but if things
 * start breaking and is related to memory,
 * this might be the issue.
 */

// 4 bytes will be allocated from this.
uintptr_t alloc_frame(pmm_struct_t* pmm) { 
    for (int byte = 0; byte < BMP_SZ; ++byte) {
        uint32_t dword = pmm->bitmap[byte];
        for (int bit = 0; bit < 32; ++bit, dword >>= 1) {
            if (!(dword & 0x1)) {       // If a bit is free.
                // Toggle the bit.
                pmm->bitmap[byte] ^= (0x1 << bit);
                // Return physical address.
                mem_used += 4;
                return 4096 * (8 * 4 * byte + bit);
            }
        }
    }
}


void free_frame(pmm_struct_t* pmm, const uintptr_t PHYS) {
    mem_used -= 4;
    pmm->bitmap[_get_byte(PHYS)] |= (0x0 << _get_bit(PHYS));
}
