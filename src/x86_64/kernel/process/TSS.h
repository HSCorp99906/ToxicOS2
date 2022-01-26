#ifndef TSS_H
#define TSS_H

#include <stddef.h>
#include "../memory/GDT.h"
#include "../memory/memset.h"

typedef struct {
    uint16_t reserved;
    uint64_t ist7High;
    uint64_t isr7Low;
    uint64_t ist6High;
    uint64_t ist6Low;
    uint64_t ist5High;
    uint64_t ist5Low;
    uint64_t ist4High;
    uint64_t ist4Low;
    uint64_t ist3High;
    uint64_t ist3Low;
    uint64_t ist2High;
    uint64_t ist2Low;
    uint64_t ist1High;
    uint64_t ist1Low;
    uint16_t reserved1;
    uint32_t rsp2High;
    uint32_t rsp2Low;
    uint32_t rsp1High;
    uint32_t rsp1Low;
    uint32_t rsp0High;
    uint32_t rsp0Low;
    uint16_t reserved;
} tss_entry_t;


void tss_init(uint32_t i, uint32_t kss, uint32_t kesp);

#endif
