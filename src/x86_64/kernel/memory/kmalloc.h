#ifndef KMALLOC_H
#define KMALLOC_H

#include <stddef.h>

void heap_init(void* begin, size_t _limit);
void* _malloc(size_t size);
void _free(void* data);
size_t get_alloc_mem();

#endif
