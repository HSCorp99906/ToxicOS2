#ifndef VMM_H
#define VMM_H

#define IDENT_OFFSET 0x1 << 46
#define PAGE_PRESENT 1 << 0
#define PAGE_RW 1 << 1
#define PAGE_USER 1 << 2
#define PAGE_WRITETHROUGH 1 << 3
#define PAGE_CACHE_DISABLE 1 << 4
#define PAGE_ACCESSED 1 << 5
#define PAGE_DIRTY 1 << 6
#define PAGE_SIZE 1 << 7
#define PAGE_GLOBAL 1 << 8
#define PAGE_SOFTWARE 1 << 9
#define PAGE_NX 1 << 63


#define ID_OFFSET 1UL << 46


#define HIGH(ADDR) (ADDR + ID_OFFSET)
#define LOW(ADDR)  (ADDR - ID_OFFSET)

#include <stddef.h>
#include "memset.h"
#include "pmm.h"

void vmm_init();
uint64_t create_address_space();


#endif
