#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

void mainMenuScreen(int val, int size) {
	int i;
	for (i = 0; i<size; i++) {
		if(i<128) {
			dataArray[i] = 0x1;
		}
		if(i>384) {
			dataArray[i] = 0x80;
		}
		if (i==0 || i==127 || i==128 || i==255 || i==256 || i==383 || i==384 || i==511) {
			dataArray[i] = 0xff;
		}
	}
}

/* Code duplication!
*/
void updateMainMenu() {
    mainMenuScreen(0,512);
    displayString(28,2,"ABC");
    display_update();
    if(getbtns() != 0)
        GAMESTATE = 2;
}
