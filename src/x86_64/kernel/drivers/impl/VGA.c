#include "../VGA.h"

void vga_puts(const char* str, char** vga, uint8_t newline) {
    for (int i = 0; i < strlen(str); ++i) {
        **vga = str[i];
        *vga += 2;
    }

    if (newline) {
        for (int i = 0; i < 80 - strlen(str); ++i) {
            **vga = ' ';
            *vga += 2;
        }
    }
}


void vga_clear(char** vga, uint8_t bg, uint8_t fg) {
    *vga = (char*)0xB8000;
    uint16_t attrib = (bg  << 4) | (fg & 0x0F);

    for (int i = 0; i < 2000; ++i) {
       **vga = ' ';
       *vga += 1;
       **vga = attrib;
       *vga += 1;
    }

    *vga = (char*)0xB8000;
}


void update_cursor(int x, int y) {
	uint16_t pos = y * 80 + x;

	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (uint8_t) (pos & 0xFF));
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}
