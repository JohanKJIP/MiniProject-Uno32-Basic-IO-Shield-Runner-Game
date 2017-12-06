#include "gameHeader.h"

void entity_init(void);

/* structs */
typedef enum EntityType {
    PLAYER, OBSTACLE, STONE, BIRD, MONSTER
} EntityType_t;

typedef struct Hitbox{
    int width;
    int height;
} Hitbox;

typedef struct Monster{
    int x;
} Monster;

typedef struct Player {
    enum EntityType type;
    int x;
    int y;
    int playerScore;
    int jumping;
    int crouching;
    int legDown;
    Hitbox hitbox;
} Player;

typedef struct Obstacle {
    enum EntityType type;
    double x;
    int y;
    Hitbox hitbox;
} Obstacle;

extern Player player;
void renderLegDown(int,int,int);
void renderLegUp(int,int,int);
void renderJumpingGround(int,int,int);
void renderJumpingAir(int,int,int);
void renderStone(int,int);
void renderCloud(int,int);
void renderWeb();
void renderParticle(int,int);
void updatePlayer();
