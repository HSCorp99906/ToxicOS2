#include "../graphics.h"

static uint8_t curFlags = MENU_ENTRY_NONE;

void drw_4_entry_menu(char* entry1, char* entry2, char* entry3, char* entry4, uint8_t flags) {
    char* vga_main = (char*)0xB8000;
    curFlags = flags;

    vga_puts("       ", &vga_main, 0);
    if (flags & MENU_ENTRY_1) { 
        vga_puts("|", &vga_main, 0);
        vga_puts(entry1, &vga_main, 0);
        vga_puts(" [X]| ", &vga_main, 0);
    } else {
        vga_puts("|", &vga_main, 0);
        vga_puts(entry1, &vga_main, 0);
        vga_puts(" []| ", &vga_main, 0);
    }

    if (flags & MENU_ENTRY_2) {
        vga_puts("|", &vga_main, 0);
        vga_puts(entry2, &vga_main, 0);
        vga_puts(" [X]| ", &vga_main, 0);
    } else {
        vga_puts("|", &vga_main, 0);
        vga_puts(entry2, &vga_main, 0);
        vga_puts(" []| ", &vga_main, 0);
    }

    if (flags & MENU_ENTRY_3) {
        vga_puts("|", &vga_main, 0);
        vga_puts(entry3, &vga_main, 0);
        vga_puts(" [X]| ", &vga_main, 0);
    } else {
        vga_puts("|", &vga_main, 0);
        vga_puts(entry3, &vga_main, 0);
        vga_puts(" []| ", &vga_main, 0); 
    }

    if (flags & MENU_ENTRY_4) {
        vga_puts("|", &vga_main, 0);
        vga_puts(entry4, &vga_main, 0);
        vga_puts(" [X]| ", &vga_main, 0);
    } else {
        vga_puts("|", &vga_main, 0);
        vga_puts(entry3, &vga_main, 0);
        vga_puts(" []| ", &vga_main, 0);
    }
}
