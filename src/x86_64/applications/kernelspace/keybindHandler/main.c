#include "../../../kernel/drivers/IO.h"   // Only driver we will use in our application.


#define MIN_CURSOR_X 18
#define MAX_CURSOR_X 35

// EXTERNEL FUNCTION DECLARATIONS.
void destub_kb_isr(void*);
void send_pic_end_int();
void debug_putc();
void _reset();
void color_change(unsigned char);
void kprint(char*);
void update_entry(unsigned char);
void _curs_move(int, int);
void _clear_screen();
// END


void kb_isr();

unsigned int cursor_x = 20;
unsigned int cursor_y = 0;

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
    static unsigned char entryNum = 1;
 
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
                displaying = 1;
                __asm__ __volatile__("mov $0x7, %eax; int $0x80"); 
            }
        } else if (scancode == 42 && curKey == CTRL) {
            curKey = CTRL_SHIFT;
        } else if (curKey == CTRL_SHIFT && ch == 'r') {
            _reset();
        } else if (scancode == 73 && entryNum < 4) {
            ++entryNum; 
            update_entry(entryNum);
            _curs_move(cursor_x += 15, cursor_y);
        } else if (scancode == 81 && entryNum > 1) {
            --entryNum;
            update_entry(entryNum); 
            _curs_move(cursor_x -= 15, cursor_y);
        } else if (scancode == 28) {
            switch (entryNum) {
                case 1:
                    _clear_screen();
                    kprint("This Operating System is made by Ian Moffett and the help of his cat, Kess.");
                    displaying = 1;
                    break;
            }
        }
    }

    if (scancode == 1 && displaying) {
        __asm__ __volatile__("mov $0x6, %eax; int $0x80");
        displaying = 0;
    } 

    send_pic_end_int();     // END OF INTERRUPT.
}
