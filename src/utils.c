//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

int getsw(void) {
    return (PORTD & 0xF00) >> 8;
}

int getbtns(void) {
    return PORTD >> 5 & 0x7;
}
