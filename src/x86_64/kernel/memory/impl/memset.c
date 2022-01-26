#include "../memset.h"


void _memset(unsigned char* src, size_t amt, unsigned char val) {
    while (amt--) {
        *src++ = val;
    }
}
