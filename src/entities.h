#include "gameHeader.h"

void entity_init(void);

/* structs */
typedef enum EntityType {
    PLAYER, OBSTACLE, STONE, BIRD
} EntityType_t;

typedef struct Hitbox{
    int width;
    int height;
} Hitbox;

typedef struct Player {
    enum EntityType type;
    int y;
    int playerScore;
    int jumping;
    int crouching;
    int legDown;
    Hitbox hitbox;
} Player;

typedef struct Obstacle {
    enum EntityType type;
    int x;
    int y;
    Hitbox hitbox;
} Obstacle;

/* render leg down running animation */
void renderLegDown(int x, int y){
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
}

/* render leg up running animation */
void renderLegUp(int x, int y){
    displayPixel(x,y-3);
    displayPixel(x,y-4);
    displayPixel(x,y-1);
    displayPixel(x+1,y-1);
    displayPixel(x+1,y-2);
    displayPixel(x+1,y-3);
    displayPixel(x+1,y-4);
    displayPixel(x+1,y-4);
    displayPixel(x+1,y-5);
    displayPixel(x+2,y);
    displayPixel(x+2,y-1);
    displayPixel(x+2,y-2);
    displayPixel(x+2,y-4);
}

/* render first jumping animation */
void renderJumpingGround(int x, int y){
    displayPixel(x+1,y-1);
    displayPixel(x+1,y-2);
    displayPixel(x+1,y-3);
    displayPixel(x+1,y-4);
    displayPixel(x+2,y-1);
    displayPixel(x+2,y-3);
    displayPixel(x+3,y);
    displayPixel(x+3,y-1);
}

/* render second jumping animation */
void renderJumpingAir(int x, int y){
    displayPixel(x,y-1);
    displayPixel(x+1,y-1);
    displayPixel(x+1,y-3);
    displayPixel(x+1,y-4);
    displayPixel(x+2,y-1);
    displayPixel(x+2,y-2);
    displayPixel(x+2,y-3);
    displayPixel(x+2,y-4);
    displayPixel(x+2,y-5);
    displayPixel(x+3,y-4);
}

/* render stone animation */
void renderStone(int x, int y){
    displayPixel(x,y);
    displayPixel(x,y-1);
    displayPixel(x,y-2);
    displayPixel(x+1,y);
    displayPixel(x+1,y-1);
    displayPixel(x+1,y-2);
    displayPixel(x+2,y);
    displayPixel(x+2,y-1);
    displayPixel(x+2,y-2);
}

/* render cloud */
void renderCloud(int x){
    displayHex(x, 0, 0x4);
    displayHex(x+1, 0, 0x4);
    displayHex(x+2, 0, 0x6);
    displayHex(x+3, 0, 0x7);
    displayHex(x+4, 0, 0x6);
    displayHex(x+5, 0, 0x6);
    displayHex(x+6, 0, 0x4);
}

/* render pixel */
void renderParticle(int x, int y){
    uint8_t movement[20] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1};
    int yIndex = x % 20;
    if(x >= 0){
        displayPixel(x, (y + movement[yIndex]));
    } else {
        displayPixel(128 + x, (y + movement[yIndex]));
    }
}
