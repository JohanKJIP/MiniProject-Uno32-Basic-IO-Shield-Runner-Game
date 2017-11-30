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
    int randomVals1[5] = {0, 0, 0, 0, 0};
    int randomVals2[5] = {1, 1, 1, 1, 1};
    int randomVals3[5] = {0, 0, 0, 0, 0};
    int randomVals4[5] = {-1, -1, -1, -1, -1};
    if(x >= 0){
        int yIndex = x % 20;
        if(yIndex < 5){
            displayPixel(x, (y + randomVals1[yIndex]));
        } else if (yIndex >= 6 && yIndex < 10){
            displayPixel(x, (y + randomVals2[yIndex - 5]));
        } else if (yIndex >= 10 && yIndex < 15){
            displayPixel(x, (y + randomVals3[yIndex - 10]));
        } else{
            displayPixel(x, (y + randomVals4[yIndex - 15]));
        }
    } else {
        int yIndex = (128 + x) % 20;
        if(yIndex < 5){
            displayPixel(128 + x, (y + randomVals1[yIndex]));
        } else if (yIndex >= 6 && yIndex < 10){
            displayPixel(128 + x, (y + randomVals2[yIndex - 5]));
        } else if (yIndex >= 10 && yIndex < 15){
            displayPixel(128 + x, (y + randomVals3[yIndex - 10]));
        } else{
            displayPixel(128 + x, (y + randomVals4[yIndex - 15]));
        }
    }
}
