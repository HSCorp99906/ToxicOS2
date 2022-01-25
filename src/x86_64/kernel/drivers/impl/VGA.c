#include "../VGA.h"

void __stack_chk_fail() {}


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


void vga_puts_dec(int dec, char** vga, uint8_t newline) {
    uint8_t dec_string[80];
    uint8_t i = 0, j, temp;
    uint8_t negative = 0;       // Is dec negative?

    if (dec == 0) dec_string[i++] = '0'; // If passed in 0, print a 0
    else if (dec < 0)  {
        negative = 1;       // Number is negative
        dec = -dec;   // Easier to work with positive values
    }

    while (dec > 0) {
        dec_string[i] = (dec % 10) + '0';    // Store next digit as ascii
        dec /= 10;                           // Remove last digit
        i++;
    }

    if (negative) dec_string[i++] = '-';    // Add negative sign to front

    dec_string[i] = '\0';   // Null terminate

    // Number stored backwards in dec_string, reverse the string by swapping each end
    //   until they meet in the middle
    i--;    // Skip the null byte
    for (j = 0; j < i; j++, i--) {
        temp          = dec_string[j];
        dec_string[j] = dec_string[i];
        dec_string[i] = temp;
    }

    // Print out result
    vga_puts(dec_string, vga, newline);
}
