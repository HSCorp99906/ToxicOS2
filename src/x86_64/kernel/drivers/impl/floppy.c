#include "../floppy.h"

extern char* vga_main;

void floppy_detect_drives() {
    outportb(0x70, 0x10);
    unsigned int drives = inportb(0x71);
    vga_puts(" - Floppy drive 0: ", &vga_main, 0);
    vga_puts(drive_types[drives  >> 4], &vga_main, 1);
}

