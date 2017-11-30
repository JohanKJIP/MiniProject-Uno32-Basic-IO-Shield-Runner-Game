#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

void gameOverScreen(int val, int size) {
	int i;
	for (i = 0; i<size; i++) {
		if(i<128) {
			dataArray[i] = 0x1;
		}
		if(i>384) {
			dataArray[i] = 0x80;
		}
	}
}

/*
*/
void updateGameOver() {
    gameOverScreen(0,512);
    display_update();
    sleep(1000000);
    if(getbtns() != 0)
        GAMESTATE = 1;
}
