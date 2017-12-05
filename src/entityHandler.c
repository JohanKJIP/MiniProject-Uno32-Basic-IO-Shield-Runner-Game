#include <stdint.h>
#include "entities.h"
#include "gameHeader.h"

#define PLAYER_X 10
#define FLOOR_Y_UP 29
#define FLOOR_Y_DOWN 8
Player player;                      //player entity

/* obstacle variable */
#define MAX_OBSTACLE_AMOUNT 10
Obstacle obstacles[MAX_OBSTACLE_AMOUNT];         //obstacle array
int obstacleAmount = 0;

/* jump variables */
int jumpDelta = 60;                 //should be incremented by dimCounter later on

/* counters */
int legCounter = 0;
int backgroundCounter = 0;
int particleX = 128;
int cloudX = 0;

/* upside down variables */
int upsideDown = 0;
int upsideDownValue = 0;
int dimCounter = 50;

/* add obstacle to array */
void add_obstacle(){
    if(obstacleAmount < MAX_OBSTACLE_AMOUNT){
        Obstacle obstacle = { .type = STONE, .x = 129, .y = FLOOR_Y_UP, .hitbox = { .width = 3, .height = 3} }; //TODO randomize size
        obstacles[0] = obstacle;
    }
}

void entity_init() {
    player.type = PLAYER;
    player.y = FLOOR_Y_UP; //floor level
    player.playerScore = 0;
    player.jumping = 0;
    player.crouching = 0;
    player.legDown = 0;
    player.hitbox.width = 4;       //preliminary width
    player.hitbox.height = 6;      //preliminary height

    add_obstacle();
}

/* render player animations */
void renderPlayer(int x, int y){
    if(player.legDown && !player.jumping) {
        renderLegDown(x, y);
    } else if(!player.legDown && !player.jumping){
        renderLegUp(x, y);
    } else if(player.jumping && player.y > 25){
        renderJumpingGround(x, y);
    } else {
        renderJumpingAir(x, y);
    }
}

/* render entities */
void render(EntityType_t type, int x, int y) {
    switch(type) {
        case PLAYER:
            renderPlayer(x, y);
            break;
        case BIRD:
            break;
        case STONE:
            renderStone(x, y);
            break;
    }
}

/* check for collision between
   player and obstacles */
checkCollisions(){
    int i;
    for(i = 0; i < 1; i++){
        if(PLAYER_X == obstacles[i].x || PLAYER_X == obstacles[i].x + obstacles[i].hitbox.width) {
            if(player.y > obstacles[i].y - obstacles[i].hitbox.height) {
                obstacles[i].x = 129;
                upsideDown = 0;
                upsideDownValue = 0;
                dimCounter = 50;
                GAMESTATE = 3;
            }
        }
    }
}

/* jumping function */
void playerJump() {
    if(jumpDelta >= 27 && getbtns() == 4) {
        jumpDelta = 0;
        player.jumping = 1;
    } else if(jumpDelta < 27 && player.y <= FLOOR_Y_UP && !upsideDown) {
        jumpDelta++;
        player.y = (((jumpDelta - 27) * jumpDelta*jumpDelta) / 240) + 29;
        if(jumpDelta == 20 && dimCounter == 50) dimCounter = 0;
    } else if(jumpDelta < 27 && player.y >= FLOOR_Y_DOWN && upsideDown){
        jumpDelta++;
        player.y = -(((jumpDelta - 27) * jumpDelta*jumpDelta) / 240) + 8;
        if(jumpDelta == 20 && dimCounter == 50) dimCounter = 0;
    }else{
        if(!upsideDown) player.y = FLOOR_Y_UP;
        else player.y = FLOOR_Y_DOWN;
        jumpDelta = 27;
        player.jumping = 0;
    }
    if(getbtns() != 2) {
        player.crouching = 0;
        player.hitbox.height = 10;
    }
}

void updatePlayer() {
    //get switches buttons, check correct answer etc.etc.
    //check collissions etc.etc.
    playerJump();

    legCounter++;
    if(legCounter == 5){
        player.legDown = 1;
    } else if(legCounter == 10){
        player.legDown = 0;
        legCounter = 0;
    }
}

void updateObstacles() {
    //TODO
    //update obstacle array
    //render obstacles
    //spawn new ones?
    if(obstacles[0].x < -2){
        obstacles[0].x = 128;
    }
    obstacles[0].x -= 1;
}

/* update background animations */
void updateBackground(){
    backgroundCounter++;
    if(backgroundCounter > 129){
        backgroundCounter = 0;
    }

    if(!upsideDown){
        renderCloud(128 - cloudX, 0);
        renderCloud(150 - cloudX, 2);
        renderCloud(200 - cloudX, 1);
    }

    if(upsideDown){
        renderParticle(particleX, 11);
        renderParticle(particleX - 20, 27);
        renderParticle(particleX - 40, 15);
        renderParticle(particleX - 70, 30);
        renderParticle(particleX - 90, 22);
        renderParticle(particleX - 100, 19);
        renderParticle(particleX - 110, 25);
        renderParticle(particleX - 120, 12);
    }

    if(upsideDown) renderWeb();

    if(backgroundCounter % 2) particleX--;

    if(backgroundCounter % 4 == 0) cloudX++;

    if(particleX == 0) particleX = 128;

    if(cloudX > 200 + 6) cloudX = 0; //128 + cloud width
}

/* change ground dimension */
void changeDimension(){
    if(dimCounter <= 49){
        dimCounter++;
        if(!upsideDown){
            if(dimCounter <= 20){
                upsideDownValue++;
            } else if(dimCounter <= 32) {
                if((dimCounter - 20) % 2) upsideDownValue ++;
            } else if(dimCounter <= 40){
                if((dimCounter - 32) % 3 == 2) upsideDownValue ++;
            } else if(dimCounter <= 49){
                if((dimCounter - 40) % 4 == 3) upsideDownValue ++;
            } else{
                upsideDownValue = 31;
                upsideDown = 1;
            }
        } else {
            if(dimCounter <= 20){
                upsideDownValue--;
            } else if(dimCounter <= 32) {
                if((dimCounter - 20) % 2) upsideDownValue --;
            } else if(dimCounter <= 40){
                if((dimCounter - 32) % 3 == 2) upsideDownValue --;
            } else if(dimCounter <= 49){
                if((dimCounter - 40) % 4 == 3) upsideDownValue --;
            } else{
                upsideDownValue = 0;
                upsideDown = 0;
            }
        }
    }
}

void entities_update() {
    updatePlayer();
    updateObstacles();
    updateBackground();
    checkCollisions();
    changeDimension();

    render(obstacles[0].type, obstacles[0].x, obstacles[0].y);
    render(PLAYER,PLAYER_X,player.y);
    /* Check collisions last! This is where we change state! */
    checkCollisions();
}
