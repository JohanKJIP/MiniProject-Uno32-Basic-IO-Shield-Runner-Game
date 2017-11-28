#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

/* Code duplication!
*/
void updateMainMenu(FPS) {
    display_update();
    if(getbtns() != 0)
        GAMESTATE = 2;
}
