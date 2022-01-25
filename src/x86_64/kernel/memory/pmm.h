/*
 * Physical memory manager.
 */

#ifndef PMM_H
#define PPM_H

#include <stdint.h>

#define _1KB (1 << 10)
#define _1MB (1 << 21)
#define _1GB (1 << 30)


// If bit one is taken then the first 4096 bytes of physical memory is being used.

// Total memory.
#define MEMORY (64 * _1MB)

uint64_t bitmap[MEM_LIMIT]


#endif
