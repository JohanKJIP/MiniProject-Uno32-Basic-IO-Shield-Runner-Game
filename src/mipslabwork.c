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

int mytime = 0x0;
volatile int* ledp;
int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void ) {
    if (timeoutcount>9 && (IFS(0) & 0x100)>>8) {
        time2string( textstring, mytime );
        display_string( 3, textstring );
        display_update();
        tick( &mytime );
        timeoutcount = 0;
    }
    IFS(0) &= 0xFFFFFEFF;
    timeoutcount++;

    if ((IFS(0) & 0x800)>> 11) {
        mytime += 3;
        IFS(0) &= 0x7FF;
    }

    /* time */
    IEC(0) |= 0x100;    //enable interrupt flag
    IPC(2) |= 0x1f;     //set priority
    /*switch */
    IEC(0) |= 0x800;    //bit 11 enable interrupt
    IPC(2) |= 0x1E000000; //bit 24-28
    enable_interrupt(); //enable gloabl interrupt
}

/* Lab-specific initialization goes here */
void init( void ) {
    /* enable led */
    volatile int* trise = (volatile int*) 0xbf886100;
    *trise &= ~0xff;

    /* set led to output PORTE */
    ledp = (volatile int*) 0xbf886110;
    *ledp = 0;

    /*  enable buttons to input */
    TRISD |= 0xFE0;

    /* timer */
    T2CON |= 0x8000; //timer 2 control register
    T2CON |= 0x70;
    PR2 = 31250; //period register
}

/**
 * Set current time.
 * @param switches
 * @param buttons
 */
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

/**
 * Convert binary to hex number.
 * @param binary
 * @return
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

void checkbuttons(){
    int buttons = getbtns();
    if(buttons != 0){
        int switches = getsw();
        setTime(switches, buttons);
    }
}

/* This function is called repetitively from the main program */
void update( void ) {
    checkbuttons();
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    *ledp = *ledp + 1;
}
