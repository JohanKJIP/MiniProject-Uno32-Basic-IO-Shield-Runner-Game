/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";
volatile int* ledp;

/* Interrupt Service Routine */
void user_isr( void ) {
    return;
}

/* Lab-specific initialization goes here */
void labinit( void ) {
    /* enable led */
    volatile int* trise = (volatile int*) 0xbf886100;
    *trise &= ~0xff;

    /* set led to output PORTE */
    ledp = (volatile int*) 0xbf886110;
    *ledp = 0;

    /*  enable buttons to input */
    TRISD |= 0xFE0;
}

void setTime(int switches, int buttons){
    buttons <<= 1;
    int hexButtons = hexConverter(buttons); //convert to hex
    int inverted = hexButtons^0xffff;       //invert bits

    /* switch = 3 => 0x3333 */
    int hexSwitches = 0x0;
    int i;
    for (i = 0; i < 4; i++) {
        hexSwitches += switches;
        hexSwitches <<= 4;
    }
    hexSwitches >>= 4;

    /* mask mytime */
    mytime = (mytime & inverted) | (hexButtons & hexSwitches);
}

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

void checkbuttons(){
    int buttons = getbtns();
    if(buttons != 0){
        int switches = getsw();
        setTime(switches, buttons);
    }
}

/* This function is called repetitively from the main program */
void labwork( void ) {
    delay( 1000 );
    checkbuttons();
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    *ledp = *ledp + 1;
    display_image(96, icon);
}
