#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

void mainMenuScreen() {
    //49 pixels wide
    // start at x = 40

    /* Top line */
    int j;
    for (j = 40; j<40 + 49; j++) {
        dataArray[j] = 0x80;
    }
    /* Side lines below S and R*/
    int i;
    for (i = 0; i < 4; i++) {
        displayPixel(40 + i,20); // left line on things.
        displayPixel(89 + i,20); // right line on things.
    }
    /* Normal letters */
    displayString(43,1,"TRANGE");
    displayString(43,2,"THINGS");

    /* Larger S top */
    displayHex(40, 1,0x9C);
    displayHex(41, 1,0xB6);
    displayHex(42, 1,0x22);
    displayHex(43, 1,0x22);
    displayHex(44, 1,0x9C);
    displayHex(45, 1,0x66);
    /* Larger S bottom */
    displayHex(40, 1,0x1);
    displayHex(41, 1,0x2);
    displayHex(42, 1,0x2);
    displayHex(43, 1,0x2);
    displayHex(44, 1,0x3);
    displayHex(45, 1,0x1);

    /* Larger R top */
    displayHex(84, 1,0xff);
    displayHex(85, 1,0x22);
    displayHex(86, 1,0x22);
    displayHex(87, 1,0x22);
    displayHex(88, 1,0x62);
    displayHex(89, 1,0xDC);
    /* Larger R bottom */
    displayHex(84, 1,0x3);
    displayHex(89, 1,0x3);
    displayHex(90, 1,0x2);
}

/* Code duplication!
*/
void updateMainMenu() {
    mainMenuScreen();

    display_update();
    if(getbtns() != 0)
        GAMESTATE = 2;
}
