/*  Header file for game */

/* Display-related functions from displayUtil.c */
void displayPixel(int x, int y);
void display_init(void);
void display_update(void);
void sleep(int);

/* Functions from utils.c */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

/* Functions from Main.c */
void updateRunning(int);
extern int GAMESTATE;

/* Functions from gameRunning.c */
int getRandomInt(int);

/* Functions from entityHandler */
void entities_update(void);

/* structs */
struct player {
    int xPos;
    int yPos;
    int PLAYER_SCORE;
    int JUMPING;
    int LEFT_LEG_DOWN;
};

struct obstacle {
    int xPos;
    int yPos;
};
