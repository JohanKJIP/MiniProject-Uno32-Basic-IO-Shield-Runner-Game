#include <stdint.h>
#include "entities.h"
#include "gameHeader.h"

#define PLAYERX 10
Player player;              //player entity
Obstacle obstacles[3];      //obstacle array

/* jump variables */
int jumpDelta = 10;

void entity_init() {
    player.type = PLAYER;
    player.y = 31; //floor
    player.playerScore = 0;
    player.jumping = 0;
    player.legDown = 0;

    //TODO Create obstacle storage datastructure.
}

void render(EntityType_t type, int x, int y) {
    switch(type) {
        case PLAYER:
            //TODO Make character pixel art
            displayPixel(x,y);
            displayPixel(x,y-1);
            displayPixel(x,y-2);
            displayPixel(x+1,y-1);
            break;
        case BIRD:
            //TODO Make bird pixel art
            break;
        case STONE:
            //TODO Make stone pixel art
            break;
    }
}

/* jumping function */
void playerJump() {
    player.y += (-0.5) * (jumpDelta * (jumpDelta - 10));
}

void updatePlayer() {
    //get switches buttons, check correct answer etc.etc.
    //check collissions etc.etc.
    if(getsw() == 0101 && jumpDelta >= 10) {
        jumpDelta = 0;
    }
    if(jumpDelta < 10){
        playerJump();
    }

    //checkCollisions(); //TODO
    render(PLAYER,PLAYERX,player.y);
}

void updateObstacles() {
    //TODO
    //update obstacle array
    //render obstacles
    //spawn new ones?
}

void entities_update() {
    updatePlayer();
    updateObstacles();
}
