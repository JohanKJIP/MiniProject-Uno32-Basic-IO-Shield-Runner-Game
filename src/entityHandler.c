#include <stdint.h>
#include "entities.h"
#include "gameHeader.h"

#define PLAYER_X 10
#define FLOOR_Y 31
Player player;                      //player entity

/* obstacle variable */
#define MAX_OBSTACLE_AMOUNT 10
Obstacle obstacles[MAX_OBSTACLE_AMOUNT];         //obstacle array
int obstacleAmount = 0;

/* jump variables */
int jumpDelta = 10;                 //should be incremented by timer later on

void entity_init() {
    player.type = PLAYER;
    player.y = FLOOR_Y; //floor level
    player.playerScore = 0;
    player.jumping = 0;
    player.legDown = 0;
    player.hitbox.width = 10;       //preliminary width
    player.hitbox.height = 25;      //preliminary height

    //TODO Create obstacle storage datastructure.
}

/* add obstacle to array */
void add_obstacle(){
    if(obstacleAmount < MAX_OBSTACLE_AMOUNT){
        Obstacle obstacle = { .type = OBSTACLE, .x = 130, .y = FLOOR_Y, .hitbox = { .width = 10, .height = 10} }; //TODO randomize size
        obstacles[obstacleAmount] = obstacle;
        obstacleAmount ++;
    }
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
    render(PLAYER,PLAYER_X,player.y);
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
