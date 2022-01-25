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
    return 0;
}
