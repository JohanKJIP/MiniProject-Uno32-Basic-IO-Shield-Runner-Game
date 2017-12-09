/* gameRunning.c
   Written by johvh & davidjo2.
*/

#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

int lastNumber = 0;  // last number generated by getRandomInt
int accumulator = 0;
int random = 0;
int binaryNumber;
int p = 1;

/**
 * set memory with a val
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
* "Random" hehe
*/
int getRandomInt(int i) {
    p = (p*53 + 5) % 7283;
    return p%i;
}

/**
 * Update game, this is the game loop.
 */
void updateRunning() {
    random++;
    gameScreen(0,512);
    accumulator++;
    if(accumulator > 14) {
        /* Update game depending on state */
        entities_update();
        accumulator = 0;
    }
    entities_render();
    sleep(20);
    display_update();
}
