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

/* render jumping animation */
void renderJumping(int x, int y){
    displayPixel(x+1,y-1);
    displayPixel(x+1,y-2);
    displayPixel(x+1,y-3);
    displayPixel(x+1,y-4);
    displayPixel(x+2,y-1);
    displayPixel(x+2,y-3);
    displayPixel(x+3,y);
    displayPixel(x+3,y-1);
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
