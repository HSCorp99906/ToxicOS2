#ifndef MOUSE_H
#define MOUSE_H

#include "IO.h"


void mouse_wait(unsigned char a_type);
unsigned char mouse_read();
void mouse_write(unsigned char a_write);
void mouse_install();


#endif
