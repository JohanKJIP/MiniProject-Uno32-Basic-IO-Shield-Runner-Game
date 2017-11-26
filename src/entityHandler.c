#include "entities.h"
#include "gameHader.h"

Player player;

void entity_init() {
    player.type = PLAYER;
    player.y = 31; //floor
    player.playerScore = 0;
    player.jumping = 0;
    player.legDown = 0;
}

void updatePlayer() {
    getsw();
    //get switches etc.etc.
    //check collissions etc.etc.
}

void updateObstacles() {
    //TODO
    //update obstacle array
}

void entities_update(int i) {
    updatePlayer();
    updateObstacles();
}

void render(EntityType_t type) {
    switch(type) {
        case PLAYER:
            //draw player model
            break;
        case BIRD:
            //draw BIRD
            break;
        case STONE:
            //draw STONE
            break;
    }
}
