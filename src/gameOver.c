#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

/**
* Function to draw the screen that is displayed when losing.
*/
void gameOverScreen(int val, int size) {
	int i;
	for (i = 0; i<size; i++) {
		if(i<128) {
			/* Draw upper border */
			dataArray[i] = 0x1;
		} else if(i>384) {
			/* Draw lower border */
			dataArray[i] = 0x80;
		} else {
			/* Zero the array */
			dataArray[i] = 0x0;
		}
	}
	/* Display strings */
	displayString(32, 1, "Game Over");
	displayString(36, 2, "Score: ");
	displayDigit(36 + 42, 2, SCORE);
}

/*
*/
void updateGameOver() {
    gameOverScreen(0,512);
	/* Sleep and update twice. When doing it once there is a chance the display doesn't update. (why?) */
	sleep(20);
    display_update();
	display_update();
	/* Display game over for a few seconds */
    sleep(10000000);
	/* Go to menu */
	GAMESTATE = 1;
	SCORE = 0;
}
