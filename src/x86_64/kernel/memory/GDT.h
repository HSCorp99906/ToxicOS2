#ifndef GLOBAL_DESCRIPTOR_TABLE
#define GLOBAL_DESCRIPTOR_TABLE


typedef struct {
    unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed)) _gdt_entry_t;


typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) _gdtr_t;


_gdt_entry_t _gdt[3];
_gdtr_t _gp;

void _gdt_flush();       // GDT flush declaration, just here to tell compiler it exists.


void _gdt_set_gate(int entry, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    _gdt[entry].base_low = (base & 0xFFFF);
    _gdt[entry].base_middle = (base >> 16) & 0xFF;
    _gdt[entry].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    _gdt[entry].limit_low = (limit & 0xFFFF);
    _gdt[entry].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    _gdt[entry].granularity |= (gran & 0xF0);
    _gdt[entry].access = access;
}


void _gdt_install() {
    _gp.limit = (sizeof(_gdt_entry_t) * 3) - 1;
    _gp.base = (unsigned int)&_gdt;

    _gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    _gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    _gdt_flush();

}

#endif  // GLOBAL_DESCRIPTOR_TABLE
