/*
 * Physical memory manager.
 */

#ifndef PMM_H
#define PPM_H

#include <stdint.h>
#include <stddef.h>


// If bit one of bitmap is taken then the first 4096 bytes of physical memory is being used.
#define _1KB (1 << 10)
#define _1MB (1 << 21)
#define _1GB (1 << 30)
#define RAM 64 * _1MB
#define PGE_SZ 4096
#define BMP_SZ RAM / (PGE_SZ * 8 * sizeof(uint32_t))


typedef struct {
    uint32_t bitmap[BMP_SZ];
} pmm_struct_t;


void init_pmm();
uintptr_t alloc_frame();
void free_frame();
size_t frame_bytes_allocated();
#endif
