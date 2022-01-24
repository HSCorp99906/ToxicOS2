#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../util/types.h"
#include "../drivers/VGA.h"

// Selected entries.
#define MENU_ENTRY_1 0x1
#define MENU_ENTRY_2 0x2
#define MENU_ENTRY_3 0x4
#define MENU_ENTRY_4 0x8
#define MENU_ENTRY_ALL 0xF
#define MENU_ENTRY_NONE ~(0xF)

void drw_4_entry_menu(char* entry1, char* entry2, char* entry3, char* entry4, uint8_t flags);


#endif
