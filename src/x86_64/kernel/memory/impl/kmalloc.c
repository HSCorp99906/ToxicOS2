#include "../kmalloc.h"

#define DATA_START(mem_block) (((char*) mem_block) + sizeof(mem_block_t))
#define FLAG_FREE 0x1


typedef struct _MEM_BLOCK {
    struct _MEM_BLOCK* next;
    size_t size;
    unsigned char flags;
} __attribute__((packed)) mem_block_t;


static mem_block_t* mem_head = NULL;
static mem_block_t* mem_tail = NULL;
static size_t limit = 0;
static size_t allocated = 0;


void heap_init(void* begin, size_t _limit) {
    mem_head = (mem_block_t*)begin;
    mem_head->next = NULL;
    mem_head->size = 0;
    mem_head->flags = 0;
    mem_tail = mem_head;
    limit = _limit;
    allocated = 0;
}


static mem_block_t* first_fit(size_t size);


void* _malloc(size_t size) {
    if (allocated + size > limit) {
        // Oops! No memory.
        return NULL;
    }
    
    // We get a region that is free.
    mem_block_t* region = first_fit(size);
    if (region == NULL) {
        char* next = DATA_START(mem_tail) + mem_tail->size;
        mem_tail->next = (mem_block_t*)next;
        region = mem_tail->next;
        region->size = size;
        region->flags = 0x0;
        region->next = NULL;
        mem_tail = region;
        allocated += size;
    }

    return DATA_START(region);
}


void _free(void* addr) {
    mem_block_t* curFrame = mem_head;
    
    while (curFrame != NULL && addr != DATA_START(curFrame)) {
        curFrame = curFrame->next;
    }

    curFrame->flags |= FLAG_FREE;        // Memory is now free.
}


size_t get_alloc_mem() {
    return allocated;
}

static mem_block_t* first_fit(size_t size) {
    mem_block_t* curFrame = mem_head;

    while (curFrame != NULL) {
        // We check if the memory if big enough and is free.
        if (curFrame->flags & FLAG_FREE && curFrame->size >= size) {
            // Return frame.
            return curFrame;
        }

        // Get next frame.
        curFrame = curFrame->next;
    }

    // No memory was found.
    return NULL;
}
