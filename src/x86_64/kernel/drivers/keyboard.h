#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "IO.h"
#include "../util/picutils.h"
#include "../interrupts/IDT.h"
#include "../util/types.h"

#define MAX_CHAR_LIMIT 35
#define MIN_CHAR_LIMIT 13


const uint8_t* const SC_ASCII = "\x00\x1B" "1234567890-=" "\x08"
"\x00" "qwertyuiop[]" "\x0D\x1D" "asdfghjkl;'`" "\x00" "\\"
"zxcvbnm,./" "\x00\x00\x00" " ";


__attribute__((interrupt)) void kb_isr_cmd(int_frame32_t* frame) { 
    outportb(0x20, 0x20);
}


void unmask_kb_irq() {
    outportb(PIC1_DATA_PORT, 0xFD);
}

#endif
