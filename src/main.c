//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include <pic32mx.h>
#include <stdlib.h>
#include "gameHeader.h"

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
}

/* Interrupts not used,
left here if we want to use it in the future */
void user_isr(void) {
    //do nothing.
}

/* Current game state */
int GAMESTATE = 1;
/* Current difficulty */
int DIFFICULTY;
/* Current score */
int SCORE = 0;

/* Program entry point */
int main(void) {
    /* === Code from lab */
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
    /* === Code from lab */

    /* >>> Our code  */
    /* Display setup */
	display_init();
    /* Init led, buttons and switches */
	init();
    /* Init all the entities */
    entity_init();
    /* Main game loop */
	while(1) {
        /* Update different parts of the game depending on state */
        if(GAMESTATE == 1) {
            updateMainMenu();
        } else if(GAMESTATE == 2) {
            updateRunning();
        } else if(GAMESTATE == 3) {
            updateGameOver();
        } else if(GAMESTATE == 4) {
            //updateLeaderBoard();
        }
	}
	return 0;
}
