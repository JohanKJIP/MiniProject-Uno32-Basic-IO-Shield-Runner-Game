#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

/* Code duplication!
*/
void updateGameOver() {
    display_update();
    sleep(1000000);
    if(getbtns() != 0)
        GAMESTATE = 1;
}
