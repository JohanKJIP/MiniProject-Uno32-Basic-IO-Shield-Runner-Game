#include <stdint.h>
#include "entities.h"
#include "gameHeader.h"

#define PLAYER_X 10
#define FLOOR_Y 29
Player player;                      //player entity

/* obstacle variable */
#define MAX_OBSTACLE_AMOUNT 10
Obstacle obstacles[MAX_OBSTACLE_AMOUNT];         //obstacle array
int obstacleAmount = 0;

/* jump variables */
int jumpDelta = 60;                 //should be incremented by timer later on

/* counters */
int legCounter = 0;
int backgroundCounter = 0;
int particleX = 128;
int cloudX = 0;

/* upside down variables */
int upsideDown = 0;
int upsideDownValue = 0;
int timer = 0;

/* add obstacle to array */
void add_obstacle(){
    if(obstacleAmount < MAX_OBSTACLE_AMOUNT){
        Obstacle obstacle = { .type = STONE, .x = 129, .y = FLOOR_Y, .hitbox = { .width = 3, .height = 3} }; //TODO randomize size
        obstacles[0] = obstacle;
    }
}

void entity_init() {
    player.type = PLAYER;
    player.y = FLOOR_Y; //floor level
    player.playerScore = 0;
    player.jumping = 0;
    player.crouching = 0;
    player.legDown = 0;
    player.hitbox.width = 10;       //preliminary width
    player.hitbox.height = 25;      //preliminary height

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
                GAMESTATE = 3;
                obstacles[i].x = 129;
            }
        }
    }
}

/* jumping function */
void playerJump() {
    if(jumpDelta >= 60 && getbtns() == 4) {
        jumpDelta = 0;
        player.jumping = 1;
    } else if(jumpDelta >= 60 && getbtns() == 2) {
        player.crouching = 1;
        player.hitbox.height = 3;
    } else if(jumpDelta < 60 && player.y < (FLOOR_Y + 1)) {
        player.y += (0.2) * (jumpDelta/4 * (jumpDelta/4 - 4));
        jumpDelta++;
    } else{
        player.y = FLOOR_Y;
        jumpDelta = 60;
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
    if(!upsideDown){
        if(timer <= 20){
            upsideDownValue++;
        } else if(timer <= 32) {
            if((timer - 20) % 2) upsideDownValue ++;
        } else if(timer <= 40){
            if((timer - 32) % 3 == 2) upsideDownValue ++;
        } else if(timer <= 49){
            if((timer - 40) % 4 == 3) upsideDownValue ++;
        } else{
             timer = 0;
             upsideDown = 1;
        }
    } else {
        if(timer <= 20){
            upsideDownValue--;
        } else if(timer <= 32) {
            if((timer - 20) % 2) upsideDownValue --;
        } else if(timer <= 40){
            if((timer - 32) % 3 == 2) upsideDownValue --;
        } else if(timer <= 49){
            if((timer - 40) % 4 == 3) upsideDownValue --;
        } else{
             timer = 0;
             upsideDown = 0;
        }
    }
}

void entities_update() {
    updatePlayer();
    updateObstacles();
    updateBackground();
    checkCollisions();

    timer++;
    if(!upsideDown) changeDimension();

    render(obstacles[0].type, obstacles[0].x, obstacles[0].y);
    render(PLAYER,PLAYER_X,player.y);
}
