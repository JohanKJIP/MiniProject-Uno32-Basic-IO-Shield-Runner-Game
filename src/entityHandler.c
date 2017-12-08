#include <stdint.h>
#include "entities.h"
#include "gameHeader.h"

#define PLAYER_X 10                    //player entity

/* obstacle variable */
#define MAX_OBSTACLE_AMOUNT 10
Obstacle obstacles[MAX_OBSTACLE_AMOUNT];         //obstacle array
int obstacleAmount = 0;

/* counters */
int timeCounter = 0;
int particleX = 128;
int cloudX = 0;

/* jump variables */
int jumpDelta = 60;

/* upside down variables */
int upsideDown = 0;
int upsideDownValue = 0;
int dimCounter = 50;

Player player;

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
        renderLegDown(x, y, upsideDown);
    } else if(!player.legDown && !player.jumping){
        renderLegUp(x, y, upsideDown);
    } else if(player.jumping && player.y > 25){
        renderJumpingGround(x, y, upsideDown);
    } else {
        renderJumpingAir(x, y, upsideDown);
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

void reset() {
    obstacles[0].x = 129;
    upsideDown = 0;
    upsideDownValue = 0;
    dimCounter = 50;
    GAMESTATE = 3;
}

/* check for collision between
   player and obstacles */
void checkCollisions(){
    int i;
    for(i = 0; i < 1; i++){
        if(PLAYER_X >= obstacles[i].x &&
        PLAYER_X <= obstacles[i].x + obstacles[i].hitbox.width ||
        PLAYER_X  + player.hitbox.width >= (int)obstacles[i].x &&
        PLAYER_X + player.hitbox.width <= (int)obstacles[i].x + obstacles[i].hitbox.width) {
            if(!upsideDown &&
            player.y > obstacles[i].y - obstacles[i].hitbox.height) {
                reset();
            } else if(upsideDown &&
            player.y - player.hitbox.height < obstacles[i].y) {
                reset();
            }


        }
    }
}

/* jumping function */
void playerJump() {
    if(jumpDelta >= 27 && dimCounter == 50 &&
        getbtns() == 4 && binaryToDecimal(getsw()) == binaryNumber) {
        jumpDelta = 0;
        player.jumping = 1;
        binaryNumber = getRandomInt(16);
    } else if(jumpDelta < 27) {
        jumpDelta++;
        if(player.y <= FLOOR_Y_UP && !upsideDown) player.y = (((jumpDelta - 27) * jumpDelta*jumpDelta) / 240) + 29;
        else player.y = -(((jumpDelta - 27) * jumpDelta*jumpDelta) / 240) + 8;
        if(jumpDelta == 20 && dimCounter == 50 && timeCounter % 9 == 1 && GAMESTATE == 2) dimCounter = 0;
    } else if(jumpDelta > 20 && dimCounter < 50){
        jumpDelta++;
        if(!upsideDown) player.y = -(0.015) * (jumpDelta - 20) * (jumpDelta - 52) + 23;
        else player.y = 0.015 * (jumpDelta - 20) * (jumpDelta - 52) + 13;
    } else{
        if(!upsideDown) player.y = FLOOR_Y_UP;
        else player.y = FLOOR_Y_DOWN;
        jumpDelta = 27;
        player.jumping = 0;
    }
}

void updatePlayer() {
    timeCounter++;
    //get switches buttons, check correct answer etc.etc.
    //check collissions etc.etc.
    playerJump();

    if(timeCounter % 5 == 0 && player.legDown){
        player.legDown = 0;
    } else if(timeCounter % 5 == 0 && !player.legDown){
        player.legDown = 1;
    }
}

void updateObstacles() {
    if(obstacles[0].x < -2){
        SCORE++;
        obstacles[0].x = 128;
    }
    obstacles[0].x -= 1 + 0.02*SCORE;
    if(upsideDown) {
        obstacles[0].y = FLOOR_Y_DOWN - 4;
    } else {
        obstacles[0].y = FLOOR_Y_UP;
    }
}

void renderBackground() {
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
        renderWeb();
    }
}

/* update background animations */
void updateBackground(){
    if(timeCounter % 2) particleX--;

    if(timeCounter % 4 == 0) cloudX++;

    if(particleX == 0) particleX = 128;

    if(cloudX == 206) cloudX = 0;
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
                obstacles[0].x = 135;
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
                obstacles[0].x = 135;
            }
        }
    }
}

void entities_render() {
    render(obstacles[0].type, obstacles[0].x, obstacles[0].y);
    render(PLAYER,PLAYER_X,player.y);
    renderBackground();
    displayDigit(62,1,binaryNumber);
}

void entities_update() {
    if(timeCounter > 130) timeCounter = 0;
    updatePlayer();
    updateObstacles();
    updateBackground();
    checkCollisions();
    changeDimension();
    /* Check collisions last! This is where we change state! */
    checkCollisions();
}
