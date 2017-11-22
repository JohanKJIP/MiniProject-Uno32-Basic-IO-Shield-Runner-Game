#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

int getsw(void) {
    int TEMPPORT = PORTD;
    return (TEMPPORT & 0xF00) >> 8;
}

int getbtns(void) {
    int BN2 = (PORTD & 0x20) >> 3;
    int BN3 = (PORTD & 0x40) >> 5;
    int BN4 = (PORTD & 0x80) >> 7;
    return BN2+BN3+BN4;
}
