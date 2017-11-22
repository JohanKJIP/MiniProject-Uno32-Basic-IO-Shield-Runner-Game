/* mipslabwork.c
   Written by johvh & davidjo2.
*/

#include <stdint.h>   
#include <pic32mx.h>  
#include "mipslab.h"

int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void ) {
    if (timeoutcount>9 && (IFS(0) & 0x100)>>8) {
        PORTE += 1;
        timeoutcount = 0;
    }
    IFS(0) &= 0xFFFFFEFF;
    timeoutcount++;
}

/**
 * Convert binary to hex number.
 * @param binary number
 * @return hex number
 */
int hexConverter(int binary){
    int hex = 0x0;
    int i;
    for (i = 0; i < 4; i++) {
        int tempMod = binary % 2;
        if(tempMod){
            hex += 0xf;
            hex <<= 4;
        } else {
            hex <<= 4;
        }
        binary >>= 1;
    }
    return hex;
}

/**
 * Update game, this is the game loop.
 */
void updateRunning( void ) {
    int i;
    for(i = 0; i<40; ++i) {
        displayPixel(i,1);
    }
    display_update();
}
