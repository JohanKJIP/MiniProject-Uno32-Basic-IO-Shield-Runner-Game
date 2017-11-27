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
int jumpDelta = 60;                 //should be incremented by timer later on

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
            displayPixel(x,y-3);
            displayPixel(x,y-4);
            displayPixel(x+1,y);
            displayPixel(x+1,y-1);
            displayPixel(x+1,y-2);
            displayPixel(x+1,y-3);
            displayPixel(x+1,y-4);
            displayPixel(x+1,y-5);
            displayPixel(x+2,y-2);
            displayPixel(x+2,y-4);
            displayPixel(x+3,y-1);
            displayPixel(x+3,y-2);
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
    //checka switches!
    int buttons = getbtns();
    if(jumpDelta >= 60 && buttons == 4) {
        jumpDelta = 0;
    } else if(jumpDelta >= 60 && buttons == 2) {
        //crouch
    }
    //try to jump
    if (jumpDelta < 60 && player.y < FLOOR_Y + 1) {
        player.y += 0.2 * (jumpDelta/4 * (jumpDelta/4 - 4));
        jumpDelta++;
    } else {
        player.y = FLOOR_Y;
        jumpDelta = 60;
    }
}

void updatePlayer() {
    //check collissions etc.etc.
    //checkCollisions(); //TODO
    playerJump();
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
