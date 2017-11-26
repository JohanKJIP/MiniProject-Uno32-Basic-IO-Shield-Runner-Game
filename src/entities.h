void entity_init(void);

/* structs */
typedef enum EntityType {
    PLAYER, OBSTACLE, STONE, BIRD
} EntityType_t;

typedef struct Hitbox{
    int width, height;
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
