//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include "gameHeader.h"

/* Accumulator to determine game speed */
int accumulator = 0;
/* "Random" number */
int random = 0;
/* Init the global binary number */
int binaryNumber;

/**
 * Rendering method for gamescreen.
*/
void gameScreen(int val, int size) {
    unsigned char hex[16] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
    int upsideDownIndex = ((31 - upsideDownValue)/8) + 1;
    int i;
    for (i = 0; i < size; i++) {
        if(i >= ((upsideDownIndex * 128) - 128) && i < (upsideDownIndex * 128)){
            dataArray[i] = hex[((31 - upsideDownValue) % 8)];
        } else{
            dataArray[i] = 0;
        }
    }
}

/**
* Get a "random" number.
*/
int getRandomInt(int i) {
    random = (random*53 + 5) % 7283;
    return random%i;
}

/**
 * Update game, this is the game running loop.
 */
void updateRunning() {
    /* Render game screen */
    gameScreen(0,512);
    /* Accumulator to determine game update speed */
    accumulator++;
    if(accumulator > 14) {
        /* Only update every 14th time we render */
        entities_update();
        accumulator = 0;
    }
    /* Render every cycle */
    entities_render();
    /* Update display */
    display_update();
}
