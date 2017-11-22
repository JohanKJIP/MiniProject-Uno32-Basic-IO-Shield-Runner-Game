/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "gameHeader.h"
#include <time.h>   /*TODO */
#include <stdlib.h> /*TODO */

volatile int* ledp;
/* Init basic functions */
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

    /* timer interrupt enable */
    IEC(0) |= 0x100;    //enable interrupt flag
    IPC(2) |= 0x1f;     //set priority
    /*switch interrupt enable */
    IEC(0) |= 0x800;    //bit 11 enable interrupt
    IPC(2) |= 0x1E000000; //bit 24-28
    enable_interrupt(); //enable global interrupt
}

int RUNNING = 1;
int PAUSED = 2;
int GAMEOVER = 3;

int main(void) {
    srand(time(NULL));
    int GAMESTATE = RUNNING;
        /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	display_init();
	display_update();

	init(); /* Do any lab-specific initialization */
	while( 1 ) {
        if(GAMESTATE == RUNNING) {
            updateRunning();
        } else if(GAMESTATE == PAUSED) {

        } else if(GAMESTATE == GAMEOVER) {

        }
	}
	return 0;
}
