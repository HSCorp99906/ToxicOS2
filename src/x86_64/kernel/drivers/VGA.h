#ifndef VGA_H
#define VGA_H

#include "../util/strings.h"
#include "../util/types.h"
#include "IO.h"

void vga_puts(const char* str, char** vga, uint8_t newline);
void vga_clear(char** vga, uint8_t bg, uint8_t fg);
void update_cursor(int x, int y);

#endif
