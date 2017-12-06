/*  Header file for game functions */
#include <stdint.h>

/* Display-related functions from displayUtil.c */
void displayPixel(int, int);
void displayHex(int,int,int);
void display_init(void);
void display_update(void);
void displayString(int,int,char*);
void displayDigit(int,int,int);
void sleep(int);
uint8_t dataArray[512];

/* Functions from utils.c */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

/* Functions from Main.c */
void updateRunning(void);
void updateMainMenu(void);
void updateGameOver(void);
void updateLeaderBoard(void);
extern int GAMESTATE;
extern int DIFFICULTY;
extern int SCORE;

/* Functions from gameRunning.c */
int getRandomInt(int);

/* Functions from entityHandler */
void entities_update(void);
void entities_render(void);
extern int timeCounter;
extern int upsideDown;
extern int upsideDownValue;
#define FLOOR_Y_UP 29
#define FLOOR_Y_DOWN 8
