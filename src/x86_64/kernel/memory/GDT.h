#ifndef GDT_H
#define GDT_H


typedef struct {
    // Limits.
    unsigned short limit_low;
    // Segment addresses (useless in 64-bit long mode).
    unsigned short base_low;
    unsigned char base_middle;
    // Access modes.
    unsigned char access;
    unsigned char gran;
    unsigned char base_high;
    
} __attribute__((packed)) gdt_entry_t;


typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) gdtr_t;


void _gdt_flush();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, char access, unsigned char gran);
void gdt_install();
void set_kernel_stack(uint64_t ptr);

#endif
