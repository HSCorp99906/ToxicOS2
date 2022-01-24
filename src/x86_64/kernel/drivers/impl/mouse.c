#include "../mouse.h"


void mouse_wait(unsigned char a_type) {
    unsigned int _time_out = 100000;

    if (!(a_type)) {
        while (_time_out--) {
            if (inportb(0x64) & 0x1) {
                return;
            }
        }

        return;
    } else {
        while (_time_out--) {
            if (!(inportb(0x64) & 0x2)) {
                return;
            }
        }

        return;
    }
}


unsigned char mouse_read() {
    mouse_wait(0);
    return inportb(0x60);
}


void mouse_write(unsigned char a_write) {
    // Wait to be able to send a command
    mouse_wait(1);
    // Tell the mouse we are sending a command
    outportb(0x64, 0xD4);
    // Wait for the final part
    mouse_wait(1);
    // Finally write
    outportb(0x60, a_write);
}


void mouse_install() {
    unsigned char _status;

    // Enable the auxiliary mouse device
    mouse_wait(1);
    outportb(0x64, 0xA8);
 
    // Enable the interrupts
    mouse_wait(1);
    outportb(0x64, 0x20);
    mouse_wait(0);
    _status=(inportb(0x60) | 2);
    mouse_wait(1);
    outportb(0x64, 0x60);
    mouse_wait(1);
    outportb(0x60, _status);
 
    // Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read();  // Acknowledge
 
    // Enable the mouse
    mouse_write(0xF4);
    mouse_read();  // Acknowledge 
}

