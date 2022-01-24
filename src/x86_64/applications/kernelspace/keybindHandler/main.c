#include "../../../kernel/drivers/IO.h"   // Only driver we will use in our application.


#define MIN_CURSOR_X 18
#define MAX_CURSOR_X 35

// EXTERNEL FUNCTION DECLARATIONS.
void destub_kb_isr(void*);
void send_pic_end_int();
void debug_putc();
void _reset();
// END


void kb_isr();

unsigned int cursor_x = 18;
unsigned int cursor_y = 2;

const unsigned char* const SC_ASCII = "\x00\x1B" "1234567890-=" "\x08"
"\x00" "qwertyuiop[]" "\x0D\x1D" "asdfghjkl;'`" "\x00" "\\"
"zxcvbnm,./" "\x00\x00\x00" " ";

int _ssmain() {
    destub_kb_isr(kb_isr);
    return 0;
}


typedef enum {
    CTRL,
    CTRL_SHIFT,
    NONE,
} special_keys_t;


void kb_isr() {
    unsigned short scancode = inportb(0x60);
    static unsigned char displaying = 0;
    char ch = SC_ASCII[scancode]; 

    static special_keys_t curKey = NONE;
    
    if (!(displaying)) {
        if (scancode == 29) {
            curKey = CTRL;
        } else if (scancode == 29 && curKey == CTRL) {
            curKey = NONE;
        } else if (scancode == 83) {
            curKey = NONE;
        } else if (ch == 'f') {
            if (curKey == CTRL) {
                curKey = NONE;
                __asm__ __volatile__("mov $0x7, %eax; int $0x80");
                displaying = 1;
            }
        } else if (scancode == 42 && curKey == CTRL) {
            curKey = CTRL_SHIFT;
        } else if (curKey == CTRL_SHIFT && ch == 'r') {
            _reset();
        }

    }

    if (scancode == 1 && displaying) {
        __asm__ __volatile__("mov $0x6, %eax; int $0x80");
        displaying = 0;
    }

    send_pic_end_int();     // END OF INTERRUPT.
}
