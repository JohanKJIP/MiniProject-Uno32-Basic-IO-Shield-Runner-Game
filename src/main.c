//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include <pic32mx.h>
#include <stdlib.h>
#include "gameHeader.h"

/* Current game state */
int GAMESTATE = 1;
/* Current difficulty */
int DIFFICULTY;
/* Current score */
int SCORE = 0;

/* Program entry point */
int main(void) {
    /* === Code from lab */
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

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
    /* Init all the entities */
    entity_init();
    /* Main game loop */
	while(1) {
        clearDisplay();
        if(GAMESTATE == 1) {
            updateMainMenu();
        } else if(GAMESTATE == 2) {
            updateRunning();
        } else if(GAMESTATE == 3) {
            updateGameOver();
        } else if(GAMESTATE == 4) {
            updateHighScores();
        }
	}
	return 0;
}
