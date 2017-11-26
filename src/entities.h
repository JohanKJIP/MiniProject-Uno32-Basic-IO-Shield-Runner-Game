/* structs */
typedef enum EntityType {
    PLAYER, OBSTACLE, STONE, BIRD
} EntityType_t;

typedef struct Player {
    enum EntityType type;
    int y;
    int playerScore;
    int jumping;
    int legDown;
} Player;

typedef struct Obstacle {
    enum EntityType type;
    int x;
    int y;
} Obstacle;
