#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

/* get input from switches */
int getsw(void) {
    return (PORTD & 0xF00) >> 8;
}

/* get input from buttons */
int getbtns(void) {
    return (PORTF << 3 & 0x8) || (PORTD >> 5 & 0x7);
}
