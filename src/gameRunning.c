/* gameRunning.c
   Written by johvh & davidjo2.
*/

#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

int timeoutcount = 0;
int lastNumber = 0;  // last number generated by getRandomInt

/* Interrupt Service Routine */
void user_isr( void ) {
    if (timeoutcount>9 && (IFS(0) & 0x100)>>8) {
        PORTE += 1;
        timeoutcount = 0;
    }
    IFS(0) &= 0xFFFFFEFF;
    timeoutcount++;
}

/*
* Generate random integer depending
* on how many switches are activated
* @param switchAmount
* @return random int
*/
/*
int getRandomInt(int switchAmount){
    int random = lastNumber;
    while(lastNumber == random){
        switch(switchAmount){
            case 2:
                random = rand() % 4;
                break;
            case 3:
                random = rand() % 5 + 3;
                break;
            case 4:
                random = rand() % 11 + 5;
                break;
        }
    }
    lastNumber = random;
    return random;
}
*/

/**
 * Update game, this is the game loop.
 */
void updateRunning(FPS) {
    entities_update();
    display_update();
}
